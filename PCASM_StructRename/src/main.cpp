/*
Renames all structs in the DTK output.

Giving them names based on their variable members.

ie LBL_STRUCT_FLOAT_XXX
ie LBL_STRUCT_DOUBLE_XXX
ie LBL_STRUCT_SKIP_RESERVE_ADDRESS_XXX
ie LBL_STRUCT_XXX
*/

#include <PowerPCParser/Lexing/Lexer.hpp>
#include <PowerPCParser/Lexing/StructGeneration.hpp>

#include <BTDSTD/String.hpp>

#include <unordered_map>
#include <filesystem>
#include <thread>

//defines a file of ASM we are going to process
struct ASMFile
{
	std::string filepath = "", //path to file
		filename = "", //file name
		ASMCode = ""; //raw code

	std::vector<std::string> lblSymbols; //the lbl symbols
};

//performs a rename of the all the ASM code in a file
static inline ASMFile ASMCodeRename_File(ASMFile file, const std::vector<PPC::Token::Token> symbolTokens, const size_t symbolCount)
{
	printf("Renaming File: %s\n", file.filename.c_str());
	
	//goes through the files, renaming the symbols
	for (uint32 sym = 0; sym < symbolCount; ++sym)
	{
		const char* oldSymbolName = symbolTokens[sym].DTKSymbolData.oldIdentifierName.c_str();
		const size_t oldSymbolStrLength = strlen(oldSymbolName);

		//goes through the file
		size_t fileSymbolCount = file.lblSymbols.size();
		for (int32 i = 0; i < fileSymbolCount; ++i)
		{
			//finds and renames the source code
			if (!strcmp(file.lblSymbols[i].c_str(), oldSymbolName))
			{
				//rename
				BTD::String::ReplaceAll(file.ASMCode, oldSymbolName, symbolTokens[sym].DTKSymbolData.newIdentifierName);
				printf("\t\"%s\" to \"%s\"\n", oldSymbolName, symbolTokens[sym].DTKSymbolData.newIdentifierName.c_str());
				
				break;
			}
		}
	}

	//write the ASM code back to file
	printf("Saving File: %s\n", file.filename.c_str());
	BTD::IO::File ASMFile;
	ASMFile.Open(file.filepath.c_str(), BTD::IO::FileOP::TextWrite_OpenCreateStart);
	ASMFile.WriteText(file.ASMCode);
	ASMFile.Close();

	return file;
}

#define ASM_FILE_THREAD_COUNT 3
static bool ASM_FILE_THREAD_IS_DONE[ASM_FILE_THREAD_COUNT];
static std::thread ASMFiles_threadGroups[ASM_FILE_THREAD_COUNT];
static std::vector<ASMFile> ASMFiles_threadGroupWorkData[ASM_FILE_THREAD_COUNT];

//renames a array of ASM files
static inline void ASMCodeRename_FileArray(const uint32 threadIndex,
	const std::vector<PPC::Token::Token> symbolTokens, const size_t symbolCount)
{
	for (uint32 i = 0; i < ASMFiles_threadGroupWorkData[threadIndex].size(); ++i)
		ASMFiles_threadGroupWorkData[threadIndex][i] = ASMCodeRename_File(ASMFiles_threadGroupWorkData[threadIndex][i], symbolTokens, symbolCount);

	ASM_FILE_THREAD_IS_DONE[threadIndex] = true;
}

int main(int args, char* argv[])
{
	std::string ASMDir = "C:\\KARTools\\KAR-Decomp\\asm";
	//std::string ASMTestOutputDir = "C:\\KARTools\\KAR-Decomp\\PPC_ASMOutput";
	std::string DTKSymbolFilepath = "C:\\KARTools\\KAR-Decomp\\config\\GKYE1\\symbols.txt";

	printf("---------------GENERATING SYMBOL STRUCT DEFINITIONS------------\n");

	//loads symbol file and process it
	BTD::IO::File file;
	if (!file.Open(DTKSymbolFilepath.c_str(), BTD::IO::FileOP::TextRead_OpenExisting))
	{
		BTD::Util::Logger::LogFatalErrorToConsole("Power PC ASM To C || Rename Structs",
			"Symbol Config File", "main",
			std::string(std::string("Failed to load DTK Symbol file at \"") + DTKSymbolFilepath + "\"").c_str());
		getchar();
		return -1;
	}
	std::string symbolDataText = ""; file.ReadAllText(symbolDataText); file.Close();
	std::vector<PPC::Token::Token> symbolTokens = PPC::Parser::LexSymbolFile(symbolDataText);
	const size_t symbolCount = symbolTokens.size();

	//the global vars for tracking number of struct types
	size_t structNameCount_struct = 0, structNameCount_float = 0, structNameCount_double = 0,
		structNameCount_skip = 0, structNameCount_byte = 0, structNameCount_byte4 = 0;

	//goes through all the files and searches for object definitions and generate labeles for them based on type
	uint32 threadIndex = 0;
	for (const auto& entry : std::filesystem::directory_iterator(ASMDir))
	{
		if (!entry.is_regular_file())
			continue;

		ASMFile f;
		f.filepath = entry.path().string();

		f.filename = entry.path().filename().string();
		f.filename.resize(f.filename.size() - 2); //strip extension

		//generates token list of ASM code
		file.Open(f.filepath.c_str(), BTD::IO::FileOP::TextRead_OpenExisting);
		file.ReadAllText(f.ASMCode);
		file.Close();
		std::vector<PPC::Token::Token> tokens = PPC::Parser::LexASMIntoTokesn(f.ASMCode);

		//gets lbl struct identitfiers
		f.lblSymbols.reserve(15); const size_t tokenCount = tokens.size();
		for (uint32 c = 0; c < tokenCount; ++c)
		{
			//first check for object/struct start/end
			if (c + 1 < tokenCount && tokens[c].type == PPC::Token::TokenType::DotDirective &&
				tokens[c].directiveMetadata.directive == PPC::Util::DotDirective::ObjectStart)
			{
				//checks if it's a "lbl_" object
				c++;
				if (tokens[c].data[0] == 'l' &&
					tokens[c].data[1] == 'b' &&
					tokens[c].data[2] == 'l' &&
					tokens[c].data[3] == '_')
					f.lblSymbols.emplace_back(tokens[c].data);
			}

			//check for out in the wild uses
			else if (tokens[c].data[0] == 'l' &&
				tokens[c].data[1] == 'b' &&
				tokens[c].data[2] == 'l' &&
				tokens[c].data[3] == '_')
			{
				//if it has a @
				if (tokens[c].data.find("@") != std::string::npos)
					f.lblSymbols.emplace_back(BTD::String::SplitStrByChar(tokens[c].data, '@')[0]);
				else
					f.lblSymbols.emplace_back(tokens[c].data);
			}
		}

		//generates struct definitions
		std::vector<PPC::Lexer::StructDefinition::StructDefinition> structDefs = PPC::Lexer::StructDefinition::GenerateStructDefinitions(tokens);

		//goes through the symbols and cross ref the struct definitons to generate proper names for the structs
		for (uint32 i = 0; i < structDefs.size(); ++i)
		{
			const char* structName = structDefs[i].name.c_str();

			//check what variables are inside and flag what kind of struct it is
			for (uint32 sym = 0; sym < symbolCount; ++sym)
			{
				//checks if they match
				if (!strcmp(structName, symbolTokens[sym].DTKSymbolData.oldIdentifierName.c_str()))
				{
					symbolTokens[sym].DTKSymbolData.newIdentifierName = std::string("LBL_STRUCT_");

					const size_t varCount = structDefs[i].vars.size();
					std::string structTypeNum = "";

					//if there are more then one variabel
					if (varCount > 0)
					{
						//if there's only one datatype
						if (varCount == 1)
						{
							//changes based on the datatype
							switch (structDefs[i].vars[0].datatype)
							{
							case PPC::Util::Datatype::Skip_Uint16: //defines a skip which is just a uint16
								structTypeNum = std::string("SPACE_RESERVE_SKIP_") + std::to_string(structNameCount_skip);
								structNameCount_skip++;
								break;

							case PPC::Util::Datatype::Float: //defines a float
								structTypeNum = std::string("FLOAT_") + std::to_string(structNameCount_float);
								structNameCount_float++;
								break;
							case PPC::Util::Datatype::Double: //defines a double
								structTypeNum = std::string("DOUBLE_") + std::to_string(structNameCount_double);
								structNameCount_double++;
								break;

							case PPC::Util::Datatype::Byte: //defines a byte
								structTypeNum = std::string("BYTE_") + std::to_string(structNameCount_byte);
								structNameCount_byte++;
								break;
							case PPC::Util::Datatype::Byte_4: //defines a 4byte
								structTypeNum = std::string("BYTE4_") + std::to_string(structNameCount_byte4);
								structNameCount_byte4++;
								break;

								//default fallback for the ass covering
							default:
								structTypeNum = std::to_string(structNameCount_struct);
								structNameCount_struct++;
								break;
							}
						}

						//if we have to check multiable variabeles
						else
						{
							//checks the variables are all the same
							bool isSame = true;
							PPC::Util::Datatype matchingDatatype = structDefs[i].vars[0].datatype;
							for (uint32 v = 1; v < varCount; ++v)
							{
								if (structDefs[i].vars[v].datatype != matchingDatatype)
								{
									isSame = false;
									break;
								}
							}

							//if not the same
							if (!isSame)
							{
								structTypeNum = std::to_string(structNameCount_struct);
								structNameCount_struct++;
							}

							//if they are
							else
							{
								//changes based on the datatype
								switch (matchingDatatype)
								{
								case PPC::Util::Datatype::Skip_Uint16: //defines a skip which is just a uint16
									structTypeNum = std::string("SPACE_RESERVE_SKIP_") + std::to_string(structNameCount_skip);
									structNameCount_skip++;
									break;

								case PPC::Util::Datatype::Float: //defines a float
									structTypeNum = std::string("FLOAT_") + std::to_string(structNameCount_float);
									structNameCount_float++;
									break;
								case PPC::Util::Datatype::Double: //defines a double
									structTypeNum = std::string("DOUBLE_") + std::to_string(structNameCount_double);
									structNameCount_double++;
									break;

								case PPC::Util::Datatype::Byte: //defines a byte
									structTypeNum = std::string("BYTE_") + std::to_string(structNameCount_byte);
									structNameCount_byte++;
									break;
								case PPC::Util::Datatype::Byte_4: //defines a 4byte
									structTypeNum = std::string("BYTE4_") + std::to_string(structNameCount_byte4);
									structNameCount_byte4++;
									break;

									//default fallback for the ass covering
								default:
									structTypeNum = std::to_string(structNameCount_struct);
									structNameCount_struct++;
									break;
								}
							}
						}
					}

					//anything else || set to normal struct || this a fallback just to cover our ass
					else
					{
						structTypeNum = std::to_string(structNameCount_struct);
						structNameCount_struct++;
					}

					//sets the name
					symbolTokens[sym].DTKSymbolData.newIdentifierName += structTypeNum;

					break;
				}
			}
		}

		//adds to one of the thread groups
		ASMFiles_threadGroupWorkData[threadIndex].emplace_back(f);
		threadIndex++;
		if (threadIndex >= ASM_FILE_THREAD_COUNT)
			threadIndex = 0;

	}

	printf("---------------FINISHED GENERATING SYMBOL STRUCT DEFINITIONS------------\n");

	printf("---------------STARTED WRITING SYMBOL DATA------------\n");

	//searches through the symbols and rename them
	for (uint32 i = 0; i < symbolCount; ++i)
		symbolDataText.replace(symbolDataText.find(symbolTokens[i].DTKSymbolData.oldIdentifierName), symbolTokens[i].DTKSymbolData.oldIdentifierName.size(),
			symbolTokens[i].DTKSymbolData.newIdentifierName.c_str());

	//write symbol data back to file
	if (!file.Open(DTKSymbolFilepath.c_str(), BTD::IO::FileOP::TextWrite_OpenCreateStart))
	{
		BTD::Util::Logger::LogFatalErrorToConsole("Power PC ASM To C || Rename Structs",
			"Symbol Config File", "main",
			std::string(std::string("Failed to write renamed symbol data back to DTK symbol file at \"") + DTKSymbolFilepath + "\"").c_str());
		getchar();
	}
	file.WriteText(symbolDataText);
	file.Close();

	printf("---------------FINISHED WRITING SYMBOL DATA------------\n");

	printf("---------------RENAMING STRUCTS IN ASM------------\n");

	//fire off each of the threads
	memset(ASM_FILE_THREAD_IS_DONE, false, sizeof(ASM_FILE_THREAD_IS_DONE));
	for (uint32 i = 0; i < ASM_FILE_THREAD_COUNT; ++i)
		ASMFiles_threadGroups[i] = std::thread(ASMCodeRename_FileArray, i, symbolTokens, symbolCount);

	//waits for threads
	for (uint32 i = 0; i < ASM_FILE_THREAD_COUNT; ++i)
		ASMFiles_threadGroups[i].join();

	printf("---------------DONE RENAMING STRUCTS IN ASM------------\n");

	//--cleans up
	getchar();
	return 0;
}
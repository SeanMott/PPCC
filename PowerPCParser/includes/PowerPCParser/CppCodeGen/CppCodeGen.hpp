#pragma once

//defines a C++ Code gen from fine grain AST

#include <PowerPCParser/FineGrainAST/FineGrainAST.hpp>

namespace PPC::Backend::CppCodeGen
{
	//defines the type of C++ code node
	enum class CodeGenNodeType
	{
		Comment = 0, //comment

		GenaricCodeLine, //defines a genaric line of code

		FunctionPrototype, //the prototype of a function
		FunctionImpl, //the implementation of a function

		Operator_SemiColon,	 //operator ;
		Operator_Colon,	 //operator :

		Operator_Curly_Bracket_Open, //operator {}
		Operator_Curly_Bracket_Closed, //operator {}

		JumpLabel, //jump label

		//para operator (open)
		//para operator (closed)

		ObjectPrototype, //starts the C++ struct

		ObjectEnd, //ends the C++ struct

		//NoCodeForASMInstruction, //asm instruction comment injection

		//variable definition

		//assigment operator

		//addition operator

		//keywords
		Keyword_ControlFlow,

		Count
	};

	//defines a register parameter

	//defines a register offset parameter

	//defines meta data for a ASM Instruction with no specific C++ Generation function
	//struct CodeGenNode_NoASMToCppImpl
	//{
	//	std::string rawCode = ""; //a simple string showing what the ASM instruction and parameters were
	//};

	//defines a if-branch code gen node

	//defines a addition code gen node

	//defines a subtraction code gen node

	//defines a multiplication code gen node

	//defines a divition code gen node

	//defines a jump label definition
	struct CodeGenNode_JumpLabelDefinition
	{
		std::string labelName = "";

		//code at this location
	};

	//defines function metadata
	struct CodeGenNode_Function
	{
		std::string funcName = "";
		
		//return type

		//parameters

		//body code

		//prints to the console

		//generates the C++ Code
	};

	//defines a object metadata
	struct CodeGenNode_Object
	{
		std::string objName = "";
	};

	//defines a C++ code node
	struct CodeGenNode
	{
		CodeGenNodeType type = CodeGenNodeType::Count;

		//the meta data
		CodeGenNode_Function functionMetadata; //function data
		CodeGenNode_Object objectMetadata; //object data
		std::string generalStrData = ""; //general string data

		//prints to the console
		inline std::string Print()
		{
			std::string str = "";

			switch (type)
			{
				//function prototype
			case CodeGenNodeType::FunctionPrototype:
				str = "void " + functionMetadata.funcName + "();";
				break;

				//function implementation
			case CodeGenNodeType::FunctionImpl:
				str = "void " + functionMetadata.funcName + "()";
				break;

				//jump label
			case CodeGenNodeType::JumpLabel:
				str = "\n" + generalStrData + ": //Jump Label";
				break;

				//object prototype
			case CodeGenNodeType::ObjectPrototype:
				str = "struct " + objectMetadata.objName;
				break;

				//object ende
			case CodeGenNodeType::ObjectEnd:
				str = "};\n";
				break;

				//comment
			case CodeGenNodeType::Comment:
				str = "\t//" + generalStrData;
				break;

			case CodeGenNodeType::Operator_Curly_Bracket_Open:
				str = "{";
				break;

			case CodeGenNodeType::Operator_Curly_Bracket_Closed:
				str = "}\n";
				break;


				//prints the general string data
			default:
				str = generalStrData;
				break;
			}

			str += "\n";
			printf("%s", str.c_str());
			return str;
		}
	};

	//stores two code gen nodes, one is for the header, one is for the source
	struct CppTranslationUnits
	{
		std::vector<CodeGenNode> header, source;
	};

	//generates code gen nodes from fine-grain AST
	CppTranslationUnits RunCodeGen(const std::vector<PPC::AST::SecondPass::ASTSecondPass_Node>& secondPassASTTree, const std::string& filename);

	//prints the C++ code gen first pass and dumps the data to a file
	static inline void PrintAndDump_CppCodeGen(PPC::Backend::CppCodeGen::CppTranslationUnits& translationUnits, const std::string& dumpDir, const std::string& fileName)
	{
		//prints to console and generates code
		std::string dumpText = "";
		for (uint32 i = 0; i < translationUnits.source.size(); ++i)
			dumpText += translationUnits.source[i].Print();

		//dumps into cpp file
		std::string filepath = dumpDir + "\\CppCodeGenDump_" + fileName + ".cpp";
		BTD::IO::File file; file.Open(filepath.c_str(), BTD::IO::FileOP::TextWrite_OpenCreateStart);
		file.WriteText(dumpText);
		file.Close();

		//prints to console and generates code
		dumpText = "";
		for (uint32 i = 0; i < translationUnits.header.size(); ++i)
			dumpText += translationUnits.header[i].Print();

		//dumps into header file
		filepath = dumpDir + "\\CppCodeGenDump_" + fileName + ".hpp";
		file.Open(filepath.c_str(), BTD::IO::FileOP::TextWrite_OpenCreateStart);
		file.WriteText(dumpText);
		file.Close();
	}

	//prints the C++ code gen first pass
	static inline void Print_CppCodeGen(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>& firstPassCppCodeGen)
	{
		//prints to console
		for (uint32 i = 0; i < firstPassCppCodeGen.size(); ++i)
			firstPassCppCodeGen[i].Print();
	}
}
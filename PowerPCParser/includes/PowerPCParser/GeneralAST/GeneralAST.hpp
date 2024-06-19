#pragma once

//defines a general AST first pass

#include <PowerPCParser/Lexing/Lexer.hpp>

#include <vector>

namespace PPC::AST::FirstPass
{
	//defines a first pass AST Node type
	enum class ASTFirstPass_NodeType
	{
		Variable = 0, //defines a variable

		FunctionStart, //defines the start of a function

		FunctionEnd, //defines the end of a function

		ObjectStart, //defines the start of a object

		ObjectEnd, //defines the end of a object

		AssemblyInstruction, //defines a assembly instruction

		JumpLabel, //defines a jump label

		Count
	};

	//defines a first pass AST Node
	struct ASTFirstPass_Node
	{
		ASTFirstPass_NodeType type = ASTFirstPass_NodeType::Count;
		std::vector<Token::Token> tokens;

		//prints to the console
		inline std::string Print()
		{
			std::string printStr = "";

			switch (type)
			{
				case ASTFirstPass_NodeType::Variable:
					printStr = "Variable: Datatype (" + tokens[0].data + ") Value(" + tokens[1].data + ")\n";
					break;

				case ASTFirstPass_NodeType::AssemblyInstruction:
					printStr = "Assembly Instruction: " + tokens[0].data + " || ";
					for (uint32_t i = 1; i < tokens.size(); ++i)
						printStr += " " + tokens[i].data + " ";
					printStr += "\n";
					break;

				case ASTFirstPass_NodeType::JumpLabel:
					printStr = "Jump Label: " + tokens[0].data + "\n";
					break;

				case ASTFirstPass_NodeType::FunctionStart:
					printStr = "Func: " + tokens[0].data + "\n{\n";
					break;
				case ASTFirstPass_NodeType::FunctionEnd:
					printStr = "}\n";
					break;
				
				case ASTFirstPass_NodeType::ObjectStart:
					printStr = "Object: " + tokens[0].data + "\n{\n";
					break;
				case ASTFirstPass_NodeType::ObjectEnd:
					printStr = "};\n";
					break;

				default:
					printStr = "UNKNOWN FIRST PASS AST NODE!\n";
					break;
			}

			printf(printStr.c_str());
			return printStr;
		}
	};

	//generates a first pass AST Tree
	std::vector< ASTFirstPass_Node> GenerateFirstPassASTTree(const std::vector<Token::Token>& tokens);
	
	//prints the first pass ASM AST and dumps the data to a file
	static inline void PrintAndDump_FirstPassASMAST(std::vector<PPC::AST::FirstPass::ASTFirstPass_Node>& firstPassASTTree, const std::string& dumpDir, const std::string& fileName)
	{
		std::string dumpText = "";

		//prints to console
		for (uint32 i = 0; i < firstPassASTTree.size(); ++i)
			dumpText += firstPassASTTree[i].Print();

		//dumps into file
		std::string filepath = dumpDir + "\\FAADump_" + fileName + ".txt";
		BTD::IO::File file; file.Open(filepath.c_str(), BTD::IO::FileOP::TextWrite_OpenCreateStart);
		file.WriteText(dumpText);
		file.Close();
	}

	//prints a first pass ASM AST
	static inline void Print_FirstPassASMAST(std::vector<PPC::AST::FirstPass::ASTFirstPass_Node>& firstPassASTTree)
	{
		//prints to console
		for (uint32 i = 0; i < firstPassASTTree.size(); ++i)
			firstPassASTTree[i].Print();
	}


}
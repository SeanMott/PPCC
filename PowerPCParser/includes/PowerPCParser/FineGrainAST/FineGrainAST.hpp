#pragma once

//defines a fine grain AST with added details and context to the first pass of the AST

#include <PowerPCParser/GeneralAST/GeneralAST.hpp>

namespace PPC::AST::SecondPass
{
	//defines a second pass AST Node type
	enum class ASTSecondPass_NodeType
	{
		General = 0, //general Node

		Function, //defines a function node

		JumpLabel, //defines a jump label defined in a function

		Object, //defines a object

		//defines a general register

		//defines a floating point register
		//defines a integer register
		//defines a special register
		//defines a link register

		//defines the memory offset of a register
		//defines the memory offset of a struct/object

		//gets the high bits end of a register
		//gets the low bits end of a register

		//defines a constant integer value
		//defines a hex value

		JumpAddress, //defines a jump address to move to

		ASMInstruction, //defines a assembly instruction

		Variabel, //defines a variable

		//defines a value store assembly instruction node

		//defines a register node

		//defines a function node

		//defines a already known function node

		//defines a struct/object node

		//defines a variable

		//defines a functon pointer variable

		//memory offset of register

		//defines a pointer variable

		//defines a branching assembly instruction

		//defines a arithmatic assembly instruction

		//defines a comparision assembly instruction

		//defines a hex value constant

		Count
	};

	//defines a register metadata

	//defines a assembly instruction meta data
	struct ASTSecondPass_Node_ASMInstruction
	{
		PPC::Decoder::ASM::Opcode opcode;

		std::vector<PPC::Token::Token> parameterTokens; //the tokens making up it's parameters

		//prints the node
		inline std::string Print()
		{
			std::string printStr = "ASM Instruction || Kind: General || \"" + opcode.instructionStr + "\" || Params: ";
			
			//goes through all the tokens and adds their data
			for (uint32 i = 0; i < parameterTokens.size(); ++i)
				printStr += " " + parameterTokens[i].data + " ";

			printStr += "\n";
			return printStr;
		}
	};

	//defines a jump label and it's assembly instructions
	struct ASTSecondPass_Node_JumpLabel
	{
		std::string labelName = ""; //the name of the jump address

		std::vector<ASTSecondPass_Node_ASMInstruction> instructions; //the instructions specific to this label

		//prints the node
		inline std::string Print()
		{
			std::string printStr = "Jump Label || \"" + labelName + "\":\n";

			//goes through all the tokens and adds their data
			for (uint32 i = 0; i < instructions.size(); ++i)
				printStr += instructions[i].Print();

			printStr += "\n";
			return printStr;
		}
	};

	//defines function meta data
	struct ASTSecondPass_Node_Function
	{
		std::string funcName = ""; //the name of the function

		std::vector<ASTSecondPass_Node_ASMInstruction> instructions; //the instructions for this function not inside another jump label

		std::vector<ASTSecondPass_Node_JumpLabel> jumpLabels; //the jump labels and it's instructions

		//prints the node
		inline std::string Print()
		{
			std::string printStr = "Func || \"" + funcName + "\" \n{\n";

			//goes through all the instructions and adds their data
			for (uint32 i = 0; i < instructions.size(); ++i)
				printStr += instructions[i].Print();

			//adds the jump label parts
			printStr += "\n";
			for (uint32 i = 0; i < jumpLabels.size(); ++i)
				printStr += jumpLabels[i].Print();

			printStr += "\n}\n\n";
			return printStr;
		}
	};

	//defines a variable meta data
	struct ASTSecondPass_Node_Variable
	{
		std::vector<PPC::Token::Token> tokens; //the tokens making up

		//prints the node
		inline std::string Print()
		{
			std::string printStr = "Variable || Datatype: " + tokens[0].data + " || \"" + tokens[1].data + "\"";

			printStr += "\n";
			return printStr;
		}
	};

	//defines a object metadata
	struct ASTSecondPass_Node_Object
	{
		std::string objName = ""; //the name of the object

		std::vector<ASTSecondPass_Node_Variable> variables; //defines variables

		//prints the node
		inline std::string Print()
		{
			std::string printStr = "Object || \"" + objName + "\" \n{\n";

			//goes through the variables
			for (uint32 i = 0; i < variables.size(); ++i)
				printStr += variables[i].Print();

			printStr += "\n}\n\n";
			return printStr;
		}
	};

	//defines a second pass AST node
	struct ASTSecondPass_Node
	{
		ASTSecondPass_NodeType type = ASTSecondPass_NodeType::General;

		std::vector<FirstPass::ASTFirstPass_Node> generalNodes; //the general nodes it's pulled from

		//larger constructs
		ASTSecondPass_Node_Function functionMetaData; //defines function metadata
		ASTSecondPass_Node_ASMInstruction ASMInstructionMetaData; //defines assembly instruction metadata
		ASTSecondPass_Node_JumpLabel jumpLabelMetaData; //defines jump label metadata

		//parameter constructs

		//structs/objects
		ASTSecondPass_Node_Object objMetaData; //defines the object metadata

		//prints to the console
		inline std::string Print()
		{
			std::string printStr = "";
			switch (type)
			{
			case ASTSecondPass_NodeType::General:
				printStr = generalNodes[0].Print();
				break;

			case ASTSecondPass_NodeType::Function:
				printStr += functionMetaData.Print();
				break;
			
			case ASTSecondPass_NodeType::ASMInstruction:
				printStr += ASMInstructionMetaData.Print();
				break;

			case ASTSecondPass_NodeType::JumpLabel:
				printStr += jumpLabelMetaData.Print();
				break;

			case ASTSecondPass_NodeType::Object:
				printStr += objMetaData.Print();
				break;
			
			}

			printf(printStr.c_str());
			return printStr;
		}
	};

	//generates the second pass of the AST tree
	std::vector<ASTSecondPass_Node> GenerateSecondPassASTTree(const std::vector<FirstPass::ASTFirstPass_Node>& firstPassTree);

	//prints the second pass ASM AST and dumps the data to a file
	static inline void PrintAndDump_SecondPassASMAST(std::vector<PPC::AST::SecondPass::ASTSecondPass_Node>& secondPassASTTree, const std::string& dumpDir, const std::string& fileName)
	{
		std::string dumpText = "";

		//prints to console
		for (uint32 i = 0; i < secondPassASTTree.size(); ++i)
			dumpText += secondPassASTTree[i].Print();

		//dumps into file
		std::string filepath = dumpDir + "\\SAADump_" + fileName + ".txt";
		BTD::IO::File file; file.Open(filepath.c_str(), BTD::IO::FileOP::TextWrite_OpenCreateStart);
		file.WriteText(dumpText);
		file.Close();
	}

	//prints a second pass ASM AST
	static inline void Print_SecondPassASMAST(std::vector<PPC::AST::SecondPass::ASTSecondPass_Node>& secondPassASTTree)
	{
		//prints to console
		for (uint32 i = 0; i < secondPassASTTree.size(); ++i)
			secondPassASTTree[i].Print();
	}
}
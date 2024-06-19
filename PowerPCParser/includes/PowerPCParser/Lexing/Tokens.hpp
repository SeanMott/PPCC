#pragma once

//defines various tokens for Power PC and DTK

#include <PowerPCParser/General/Keywords.hpp>

#include <PowerPCOperandDecoder/ASMOpcode.hpp>
#include <PowerPCOperandDecoder/Registers.hpp>
#include <PowerPCOperandDecoder/AssemblyInstructions.hpp>

#include <string>

namespace PPC::Token
{
	//defines token types
	enum class TokenType
	{
		Identifier = 0, //idententifier

		Comment, //comment

		//Operator_Comma, //comma operator
		Operator_Colon, //colon operator
		//Operator_LeftPara, //( operator
		//Operator_RightPara, //) operator

		Literal_String, //defines a string literal
		Literal_HexValue, //hex literals
		//float literals

		Keyword_FunctionScope, //defines a function scope keyword
		Keyword_ASMInstruction, //defines a ASM instruction keyword
		Keyword_Register, //defines a register keyword

		DotDirective, //defines a general dot directive
		DotDirective_Datatype, //defines a datatype . directive

		DTK_Symbol, //defines a DTK symbol from the file

		EndOfLine,

		Count
	};

	//converts a token type to string
	inline const char* TokenTypeToStr(const TokenType type)
	{
		switch (type)
		{
		case TokenType::Identifier:
			return "Identifier";

		case TokenType::Comment:
			return "Comment";
		
		//case TokenType::Operator_Comma:
		//	return "Comma Operator";

		case TokenType::Operator_Colon:
			return "Colon Operator";

		//case TokenType::Operator_LeftPara:
		//	return "( Operator";
		//
		//case TokenType::Operator_RightPara:
		//	return ") Operator";

		case TokenType::Literal_String:
			return "String Literal";

		case TokenType::Literal_HexValue:
			return "Hex Value";


		case TokenType::Keyword_FunctionScope:
			return "Scope Keyword";

		case TokenType::Keyword_ASMInstruction:
			return "Assembly Instruction Keyword";

		case TokenType::Keyword_Register:
			return "Register Keyword";

		case TokenType::DotDirective:
			return ". Directive";

		case TokenType::DotDirective_Datatype:
			return "Datatype Keyword";

		case TokenType::EndOfLine:
			return "End Of Line";

		case TokenType::DTK_Symbol:
			return "DTK Symbol";

		default:
			return "UNKNOWN";
		}

		return "UNKNOWN";
	}

	//defines metadata for a register
	struct Token_Metadata_Register
	{
		Decoder::Register::IntegerGeneralPurposeRegister intReg = Decoder::Register::IntegerGeneralPurposeRegister::Max; //if it's a general purpose int register, what kind
		Decoder::Register::FloatingGeneralPurposeRegister floatReg = Decoder::Register::FloatingGeneralPurposeRegister::Max; //if it's a general purpose floating register, what kind
		Decoder::Register::Register_Keword_Enum micReg = Decoder::Register::Register_Keword_Enum::Count; //if it's a register, catch all for any others
	};

	//defines metadata for a hex value
	struct Token_Metadata_HexValue
	{
		bool isNegative = false; //is it negative or postive
	};

	//defines metadata for a dot directive
	struct Token_Metadata_DotDirective
	{
		Util::DotDirective directive = Util::DotDirective::Count; //the specific derective
	};

	//defines metadata for a dot directive datatypes
	struct Token_Metadata_DotDirective_Datatype
	{
		Util::Datatype datatype = Util::Datatype::Count; //what datatype is this
	};

	//defines a symbol found in a DTK file
	struct Token_Metadata_DTKSymbol
	{
		//the type of symbol
		std::string symbolTypeString = "UNKNOWN TYPE";

		std::string oldIdentifierName = "", //the old name DTK created
			newIdentifierName = "", //the name we're replacing it with
			extraLine = ""; //the rest of the line after the identifier
	};

	//defines a token
	struct Token
	{
		TokenType type = TokenType::Count;
		std::string data = "";

		//metadata
		Token_Metadata_Register registerMetadata;
		PPC::Decoder::ASM::Opcode ASMInstructionMetadata;
		Token_Metadata_HexValue hexValueMetadata;
		Token_Metadata_DotDirective directiveMetadata;
		Token_Metadata_DotDirective_Datatype datatypeMetadata;
		Token_Metadata_DTKSymbol DTKSymbolData;

		//extra flags

		//what scope does this keyword define
	};
}
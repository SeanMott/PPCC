#pragma once

//goes through the ASM DTK code and generates struct definitions

#include <PowerPCParser/General/Keywords.hpp>
#include <PowerPCParser/Lexing/Tokens.hpp>

#include <BTDSTD/Types.hpp>

#include <vector>

namespace PPC::Lexer::StructDefinition
{
	//defines a variable in the struct
	struct StructDefinition_MemberVar
	{
		PPC::Util::Datatype datatype; //datatype
		std::string datatype_str = ""; //string version of the datatype
		std::string value = ""; //the value of the variable

		//prints data
		inline void Print()
		{
			printf("\t%s = %s\n", datatype_str.c_str(), value.c_str());
		}
	};

	//defines a struct definition
	struct StructDefinition
	{
		std::string name = ""; //the name of the struct
		std::vector<PPC::Token::Token> tokens; //tokens making up the vars || DEBUG
		std::vector<StructDefinition_MemberVar> vars; //vars making up the struct

		//prints data
		inline void Print()
		{
			for (uint32 i = 0; i < vars.size(); ++i)
				vars[i].Print();
		}
	};

	//processes a struct definition
	static inline StructDefinition GenerateStructDefinition(const std::vector<PPC::Token::Token>& ASMTokens, const size_t& tokenCount,
		uint32& tokenIndex)
	{
		StructDefinition s;
		
		//gets name
		tokenIndex++;
		s.name = ASMTokens[tokenIndex].data;

		//gather tokens
		s.tokens.reserve(15); //the tokens making it up
		while (ASMTokens[tokenIndex].type != Token::TokenType::DotDirective &&
			ASMTokens[tokenIndex].directiveMetadata.directive != Util::DotDirective::ObjectEnd)
		{
			tokenIndex++;

			//skips scoping and new line
			if (ASMTokens[tokenIndex].type == Token::TokenType::Keyword_FunctionScope ||
				ASMTokens[tokenIndex].type == Token::TokenType::EndOfLine)
				continue;

			//if we reach the end of the struct, break
			else if (ASMTokens[tokenIndex].type == Token::TokenType::DotDirective &&
				ASMTokens[tokenIndex].directiveMetadata.directive == Util::DotDirective::ObjectEnd)
				break;

			s.tokens.emplace_back(ASMTokens[tokenIndex]);
		}

		//process tokens
		for (uint32 i = 0; i < s.tokens.size(); ++i)
		{
			//if datatype
			if (s.tokens[i].type == PPC::Token::TokenType::DotDirective_Datatype)
			{
				StructDefinition_MemberVar v;
				v.datatype = s.tokens[i].datatypeMetadata.datatype;
				v.datatype_str = s.tokens[i].data;

				//gets value
				i++;
				v.value = s.tokens[i].data;

				s.vars.emplace_back(v);

			}
		}

		return s;
	}

	//parses a token list and returns the struct definitions
	static inline std::vector<StructDefinition> GenerateStructDefinitions(const std::vector<PPC::Token::Token>& ASMTokens)
	{
		std::vector<StructDefinition> structs; structs.reserve(2);
		const size_t ASMTokenLength = ASMTokens.size();
		std::string word = "";
		for (uint32 i = 0; i < ASMTokenLength; ++i)
		{
			//if it's a object
			if (ASMTokens[i].type == Token::TokenType::DotDirective &&
				ASMTokens[i].directiveMetadata.directive == Util::DotDirective::ObjectStart)
				//process a struct
				structs.emplace_back(GenerateStructDefinition(ASMTokens, ASMTokenLength, i));
		}

		return structs;
	}
}
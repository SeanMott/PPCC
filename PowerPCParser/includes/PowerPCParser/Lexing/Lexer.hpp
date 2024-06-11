#pragma once

//defines a lexer for splitting DTK Power PC into tokens

#include <PowerPCParser/Lexing/Tokens.hpp>

#include <BTDSTD/IO/File.hpp>

#include <string>
#include <vector>

namespace PPC::Parser
{
	//lexes DTK produced Power PC
	std::vector<Token::Token> LexASMIntoTokesn(const std::string& ASM);

	//prints a stream of tokens and dumps the data to a file
	static inline void PrintAndDump_ASMTokens(const std::vector<PPC::Token::Token>& tokens, const std::string& dumpDir, const std::string& fileName)
	{
		std::string dumpText = "";

		//prints to console
		for (uint32 i = 0; i < tokens.size(); ++i)
		{
			std::string printStr = std::string("Token ") + PPC::Token::TokenTypeToStr(tokens[i].type) + " || " + tokens[i].data + "\n";
			printf(printStr.c_str());
			dumpText += printStr;
		}

		//dumps into file
		std::string filepath = dumpDir + "\\TDump_" + fileName + ".txt";
		BTD::IO::File file; file.Open(filepath.c_str(), BTD::IO::FileOP::TextWrite_OpenCreateStart);
		file.WriteText(dumpText);
		file.Close();
	}

	//prints a stream of tokens
	static inline void Print_ASMTokens(const std::vector<PPC::Token::Token>& tokens)
	{
		//prints to console
		for (uint32 i = 0; i < tokens.size(); ++i)
			printf("Token %s || %s\n", PPC::Token::TokenTypeToStr(tokens[i].type), tokens[i].data.c_str());
	}

	//lexes DTK produced symbol file
	std::vector<Token::Token> LexSymbolFile(const std::string& symbolText);
}
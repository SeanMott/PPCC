#include <PowerPCParser/Lexing/Lexer.hpp>

#include <BTDSTD/String.hpp>

//defines a parser object

//peeks at the next char || returns -1 if end of file
static inline char Parser_PeekNextChar(const std::string& text, const size_t& length, size_t& currentCharIndex)
{
	if (currentCharIndex + 1 >= length)
		return -1;
	return text[currentCharIndex + 1];
}

//gets the next char || returns -1 if end of file
static inline char Parser_GetNextChar(const std::string& text, const size_t& length, size_t& currentCharIndex,
	char& lastChar, char& currentChar)
{
	lastChar = currentChar;
	currentChar = Parser_PeekNextChar(text, length, currentCharIndex);
	currentCharIndex++;
	return currentChar;
}

namespace PPC::Parser::TokenCreate
{
	//creates a end of line token
	static inline PPC::Token::Token CreateToken_EndOfLine()
	{
		PPC::Token::Token t;
		t.type = PPC::Token::TokenType::EndOfLine;
		t.data = "";
		return t;
	}

	//creates a comment token
	static inline PPC::Token::Token CreateToken_Comment(const std::string& text)
	{
		PPC::Token::Token t;
		t.type = PPC::Token::TokenType::Comment;
		t.data = text;
		return t;
	}

	//creates a colon operator token
	static inline PPC::Token::Token CreateToken_Operator_Colon()
	{
		PPC::Token::Token t;
		t.type = PPC::Token::TokenType::Operator_Colon;
		t.data = ":";
		return t;
	}

	//creates a string literal token
	static inline PPC::Token::Token CreateToken_StringLiteral(const std::string& text)
	{
		PPC::Token::Token t;
		t.type = PPC::Token::TokenType::Literal_String;
		t.data = text;
		return t;
	}

	//creates a directive token
	static inline PPC::Token::Token CreateToken_Directive(const std::string& text)
	{
		PPC::Token::Token t;
		t.type = PPC::Token::TokenType::DotDirective;
		t.data = text;
		return t;
	}

	//creates a directive token
	static inline PPC::Token::Token CreateToken_Directive(const Util::DotDirective& directive, const std::string& text)
	{
		PPC::Token::Token t;
		t.type = PPC::Token::TokenType::DotDirective;
		t.directiveMetadata.directive = directive;
		t.data = text;
		return t;
	}

	//creates a directive token
	static inline PPC::Token::Token CreateToken_Directive(const Util::DotDirective& directive)
	{
		PPC::Token::Token t;
		t.type = PPC::Token::TokenType::DotDirective;
		t.directiveMetadata.directive = directive;
		t.data = "";
		return t;
	}

	//creates a directive datatype token
	static inline PPC::Token::Token CreateToken_Directive_Datatype(const std::string& text, Util::Datatype datatype)
	{
		PPC::Token::Token t;
		t.type = PPC::Token::TokenType::DotDirective_Datatype;
		t.datatypeMetadata.datatype = datatype;
		t.data = text;
		return t;
	}

	//maps special keywords for scope
#define PPCC_SCOPE_KEYWORD_FLAG_COUNT 3
	static const char* scopeKeywordFlags[PPCC_SCOPE_KEYWORD_FLAG_COUNT] = { "global", "local", "weak"};
	static inline bool IsKeyword_Scope(const char* keyword, uint32& arrayIndex)
	{
		for (uint32 i = 0; i < PPCC_SCOPE_KEYWORD_FLAG_COUNT; ++i)
		{
			if (!strcmp(keyword, scopeKeywordFlags[i]))
			{
				arrayIndex = i;
				return true;
			}
		}

		return false;
	}

	//processes text into a token
	static inline PPC::Token::Token ProcessTextIntoToken(const std::string& text)
	{
		PPC::Token::Token t;

		//is it a hex value
		PPC::Token::Token_Metadata_HexValue hexValueData;
		if (text[0] == '0' && text[1] == 'x')
		{
			t.type = PPC::Token::TokenType::Literal_HexValue;
			t.data = text;
			hexValueData.isNegative = false;
			t.hexValueMetadata = hexValueData;
			return t;
		}

		//is it a negative hex value
		else if (text[0] == '-' && text[1] == '0' && text[2] == 'x')
		{
			t.type = PPC::Token::TokenType::Literal_HexValue;
			t.data = text;
			hexValueData.isNegative = true;
			t.hexValueMetadata = hexValueData;
			return t;
		}

		//if it a digit literal

		//check if it's a special keyword
		uint32 arrayIndex = 0;
		const char* keyword = text.c_str();

		//if scope keyword
		if (IsKeyword_Scope(keyword, arrayIndex))
		{
			t.type = PPC::Token::TokenType::Keyword_FunctionScope;
			t.data = text;
			return t;
		}

		//if register
		PPC::Token::Token_Metadata_Register registerData;
		if(PPC::Decoder::Register::IsString_GeneralIntegerRegister(keyword, arrayIndex, registerData.intReg) || 
			PPC::Decoder::Register::IsString_GeneralFloatingRegister(keyword, arrayIndex, registerData.floatReg) ||
			PPC::Decoder::Register::IsKeywordRegister(keyword, arrayIndex, registerData.micReg))
		{
			t.type = PPC::Token::TokenType::Keyword_Register;
			t.registerMetadata = registerData;
			t.data = text;
			return t;
		}

		//if assembly instruction
		PPC::Decoder::ASM::Opcode ASMData;
		if(PPC::Decoder::ASM::IsASMInstructionStr(keyword, arrayIndex, ASMData.instruction))
		{
			//get the kind it is
			PPC::Decoder::ASM::GetASMInstructionKind(ASMData.instruction, ASMData.kind);

			t.type = PPC::Token::TokenType::Keyword_ASMInstruction;
			t.ASMInstructionMetadata = ASMData;
			t.data = text;
			t.ASMInstructionMetadata.instructionStr = text;
			return t;
		}

		//otherwise it's just a identifier
		t.type = PPC::Token::TokenType::Count;
		t.data = text;
		return t;
	}
}

//maps special tokens to functions
#define PPCC_TOKEN_FLAG_COUNT 9
static const char tokenFlags[PPCC_TOKEN_FLAG_COUNT] = { ' ', '\n', '#', ',', '\"', '.', ':', '(', ')'};
#define TOKEN_FLAG_INDEX_SPACE 0
#define TOKEN_FLAG_INDEX_NEWLINE 1
#define TOKEN_FLAG_INDEX_POUND_SIGN_COMMENT 2
#define TOKEN_FLAG_INDEX_COMMA 3
#define TOKEN_FLAG_INDEX_DOUBLE_QUOTE 4
#define TOKEN_FLAG_INDEX_PERIOD 5
#define TOKEN_FLAG_INDEX_COLON 6
#define TOKEN_FLAG_INDEX_LEFT_PARA 7
#define TOKEN_FLAG_INDEX_RIGHT_PARA 8

//returns if it's a special token flag
static inline bool IsTokenFlag(const char c, uint32& indexInArray)
{
	for (uint32 i = 0; i < PPCC_TOKEN_FLAG_COUNT; ++i)
	{
		if (c == tokenFlags[i])
		{
			indexInArray = i;
			return true;
		}
	}

	return false;
}

//checks if the char is a number
static inline bool IsDigit(const char text)
{
	if (text == '0')
		return true;
	else if (text == '1')
		return true;
	else if (text == '2')
		return true;
	else if (text == '3')
		return true;
	else if (text == '4')
		return true;
	else if (text == '5')
		return true;
	else if (text == '6')
		return true;
	else if (text == '7')
		return true;
	else if (text == '8')
		return true;
	else if (text == '9')
		return true;

	return false;
}

//lexes DTK produced Power PC
std::vector<PPC::Token::Token> PPC::Parser::LexASMIntoTokesn(const std::string& ASM)
{
	//printf("---ASM CODE---\n");
	char currentChar = -1, lastChar = -1;
	size_t textLength = ASM.length();

	std::vector<PPC::Token::Token> tokens;
	tokens.reserve(256);

	//goes through the chars
	std::string currentLine = "";

	bool isLexingADigit = false;

	for(size_t charIndex = 0; charIndex < textLength; charIndex++)
	{
		lastChar = currentChar;
		currentChar = ASM[charIndex];

		//skips any tabs
		if (currentChar == '\t')
			continue;

		//if it's a special signal token
		uint32 tokenIndex = 0;
		if (IsTokenFlag(currentChar, tokenIndex))
		{
			//if we are in a number skip all this since it's a float
			if (tokenIndex == TOKEN_FLAG_INDEX_PERIOD && charIndex > 0 && IsDigit(ASM[charIndex - 1]))
			{
				currentLine += currentChar;
				continue;
			}

			//if space or new line
			if (tokenIndex == TOKEN_FLAG_INDEX_NEWLINE || tokenIndex == TOKEN_FLAG_INDEX_SPACE)
			{
				//tokenize it as either a identifier or keyword
				if (!currentLine.empty())
					tokens.emplace_back(TokenCreate::ProcessTextIntoToken(currentLine));
				currentLine = ""; //clear old data

				//if it's a new line, add a end of line token
				if (tokenIndex == TOKEN_FLAG_INDEX_NEWLINE)
					tokens.emplace_back(TokenCreate::CreateToken_EndOfLine());
			}

			//if other more specilized
			else
			{
				//if it has a . at the end, we skip the rest of the parsing || we do this mainly for the asm instructions with . at the end of them
				if (tokenIndex == TOKEN_FLAG_INDEX_PERIOD)
				{
					//checks if the previous word has any data
					if (currentLine.size() > 0)
					{
						//printf("Had a period at the end \"%s\"\n", currentLine.c_str());
						currentLine += ".";
						tokens.emplace_back(TokenCreate::ProcessTextIntoToken(currentLine));
						currentLine = "";
						continue;
					}
				}

				//if there was previous data, tokenize it as either a identifier or keyword
				if (!currentLine.empty())
					tokens.emplace_back(TokenCreate::ProcessTextIntoToken(currentLine));
				currentLine = ""; //clear old data

				//if string literal
				if (tokenIndex == TOKEN_FLAG_INDEX_DOUBLE_QUOTE)
				{
					//increment one so we don't instantly leave
					Parser_GetNextChar(ASM, textLength, charIndex, lastChar, currentChar);
					
					//goes to the end of the "
					std::string str = "";
					while (currentChar != '"')
					{
						str += currentChar;
						Parser_GetNextChar(ASM, textLength, charIndex, lastChar, currentChar);
					}
					
					//generates a string literal token
					tokens.emplace_back(TokenCreate::CreateToken_StringLiteral(str));
				}

				//if # comment
				else if (tokenIndex == TOKEN_FLAG_INDEX_POUND_SIGN_COMMENT)
				{
					//increment one so we don't instantly leave
					Parser_GetNextChar(ASM, textLength, charIndex, lastChar, currentChar);

					//goes to the end of the line
					std::string str = "";
					while (currentChar != '\n' && currentChar != -1)
					{
						str += currentChar;
						Parser_GetNextChar(ASM, textLength, charIndex, lastChar, currentChar);
					}

					//generates a # comment token
					//tokens.emplace_back(TokenCreate::CreateToken_Comment(str));
				}

				//if . directive
				else if (tokenIndex == TOKEN_FLAG_INDEX_PERIOD)
				{
					//increment one so we don't instantly leave
					Parser_GetNextChar(ASM, textLength, charIndex, lastChar, currentChar);

					//goes to the end of the line
					std::string str = "";
					while (!IsTokenFlag(currentChar, tokenIndex) && currentChar != -1)
					{
						str += currentChar;
						Parser_GetNextChar(ASM, textLength, charIndex, lastChar, currentChar);
					}

					//checks if it's a special keyword or datatype
					Util::Datatype datatype; Util::DotDirective directiveType;
					if (Util::IsDatatype(str.c_str(), tokenIndex, datatype))
					{
						tokens.emplace_back(TokenCreate::CreateToken_Directive_Datatype(str, datatype));
					}
					else if (Util::IsDotDerective(str.c_str(), tokenIndex, directiveType))
						tokens.emplace_back(TokenCreate::CreateToken_Directive(directiveType, str));
					//otherwise generates a genaric . directive token
					else
						tokens.emplace_back(TokenCreate::CreateToken_Directive(str));

					//push the char index back one just in case it's a token
					charIndex--;
				}

				//if , operator
				else if (tokenIndex == TOKEN_FLAG_INDEX_COMMA) {} //we skip it on purpose
					//generates a comma token
					//tokens.emplace_back(TokenCreate::CreateToken_Operator_Comma());

				//if : operator
				else if (tokenIndex == TOKEN_FLAG_INDEX_COLON)
					//generates a colon token
					tokens.emplace_back(TokenCreate::CreateToken_Operator_Colon());

				//if ( operator
				else if (tokenIndex == TOKEN_FLAG_INDEX_LEFT_PARA) {} //we skip it on purpose
					//generates a ( token
					//tokens.emplace_back(TokenCreate::CreateToken_Operator_LeftPara());

				//if ) operator
				else if (tokenIndex == TOKEN_FLAG_INDEX_RIGHT_PARA) {} //we skip it on purpose
					//generates a ) token
					//tokens.emplace_back(TokenCreate::CreateToken_Operator_RightPara());
			}

			continue;
		}

		//if it's a /**/ block
		if (currentChar == '/' && Parser_PeekNextChar(ASM, textLength, charIndex) == '*')
		{
			//increment one so we don't instantly leave
			Parser_GetNextChar(ASM, textLength, charIndex, lastChar, currentChar);

			//goes to the end of the "
			std::string str = "";
			while (currentChar != '/')
			{
				str += currentChar;
				Parser_GetNextChar(ASM, textLength, charIndex, lastChar, currentChar);
			}

			//generates a comment token
			//tokens.emplace_back(TokenCreate::CreateToken_Comment(str));
		}

		//if it's nothing special add it to the current line
		else
			currentLine += currentChar;
	}

	return tokens;
}

//lexes DTK produced symbol file
std::vector<PPC::Token::Token> PPC::Parser::LexSymbolFile(const std::string& symbolText)
{
	char currentChar = -1, lastChar = -1;
	size_t textLength = symbolText.length();

	std::vector<PPC::Token::Token> tokens;
	tokens.reserve(256);

	std::string lineData = "";
	for (size_t i = 0; i < textLength; ++i)
	{
		//process symbol data
		if (symbolText[i] == '\n')
		{
			//printf("%s\n", lineData.c_str());
			
			//splits data
			std::vector<std::string> params = BTD::String::SplitStrByChar(lineData, ' ');
			//BTD::String::PrintStrArray(params);
			lineData = "";

			//generates token
			PPC::Token::Token token;
			token.type = PPC::Token::TokenType::DTK_Symbol;
			
			token.DTKSymbolData.oldIdentifierName = params[0]; //identifier
			
			//type
			token.DTKSymbolData.symbolTypeString = BTD::String::SplitStrByChar(params[4], ':')[1];

			//if it's a object and starts with "lbl_"
			if (!strcmp(token.DTKSymbolData.symbolTypeString.c_str(), "object") &&
				token.DTKSymbolData.oldIdentifierName[0] == 'l' &&
				token.DTKSymbolData.oldIdentifierName[1] == 'b' &&
				token.DTKSymbolData.oldIdentifierName[2] == 'l' &&
				token.DTKSymbolData.oldIdentifierName[3] == '_')
			{
				//adds the rest of the parameters
				for (uint32 i = 1; i < params.size(); ++i)
					token.DTKSymbolData.extraLine += " " + params[i];

				tokens.emplace_back(token);
			}
		}

		//adds to line
		else
			lineData += symbolText[i];
	}

	return tokens;
}
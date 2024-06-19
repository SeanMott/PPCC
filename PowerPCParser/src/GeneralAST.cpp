#include <PowerPCParser/GeneralAST/GeneralAST.hpp>

//creates a assembly instruction
static inline PPC::AST::FirstPass::ASTFirstPass_Node ASTNodeCreate_AssemblyInstruction(const size_t& tokenCount, const std::vector<PPC::Token::Token>& tokens, uint32_t& tokenIndex)
{
	PPC::AST::FirstPass::ASTFirstPass_Node node;
	node.type = PPC::AST::FirstPass::ASTFirstPass_NodeType::AssemblyInstruction;

	//gets instruction
	node.tokens.emplace_back(tokens[tokenIndex]);

	//keep incrementing till we would hit a new line
	while (tokens[tokenIndex].type != PPC::Token::TokenType::EndOfLine)
	{
		//gets parameter for the instruction
		tokenIndex++;
		node.tokens.emplace_back(tokens[tokenIndex]);
	}

	return node;
}

//creates a jump label
static inline PPC::AST::FirstPass::ASTFirstPass_Node ASTNodeCreate_JumpLabel(const size_t& tokenCount, const std::vector<PPC::Token::Token>& tokens, uint32_t& tokenIndex)
{
	PPC::AST::FirstPass::ASTFirstPass_Node node;
	node.type = PPC::AST::FirstPass::ASTFirstPass_NodeType::JumpLabel;

	//gets name
	node.tokens.emplace_back(tokens[tokenIndex]);

	//skip the colon so we don't waste a loop
	tokenIndex++;

	return node;
}


//creates a variable token
static inline PPC::AST::FirstPass::ASTFirstPass_Node ASTNodeCreate_Variable(const size_t& tokenCount, const std::vector<PPC::Token::Token>& tokens, uint32_t& tokenIndex)
{
	PPC::AST::FirstPass::ASTFirstPass_Node node;
	node.type = PPC::AST::FirstPass::ASTFirstPass_NodeType::Variable;

	//gets datatype
	node.tokens.emplace_back(tokens[tokenIndex]);

	//gets value
	tokenIndex++;
	node.tokens.emplace_back(tokens[tokenIndex]);

	return node;
}

//creates a function start token
static inline PPC::AST::FirstPass::ASTFirstPass_Node ASTNodeCreate_FunctionStart(const size_t& tokenCount, const std::vector<PPC::Token::Token>& tokens, uint32_t& tokenIndex)
{
	PPC::AST::FirstPass::ASTFirstPass_Node node;
	node.type = PPC::AST::FirstPass::ASTFirstPass_NodeType::FunctionStart;

	//gets name
	tokenIndex++;
	node.tokens.emplace_back(tokens[tokenIndex]);

	return node;
}

//creates a function end tokoen
static inline PPC::AST::FirstPass::ASTFirstPass_Node ASTNodeCreate_FunctionEnd(const size_t& tokenCount, const std::vector<PPC::Token::Token>& tokens, uint32_t& tokenIndex)
{
	PPC::AST::FirstPass::ASTFirstPass_Node node;
	node.type = PPC::AST::FirstPass::ASTFirstPass_NodeType::FunctionEnd;

	return node;
}

//creates a object start token
static inline PPC::AST::FirstPass::ASTFirstPass_Node ASTNodeCreate_ObjectStart(const size_t& tokenCount, const std::vector<PPC::Token::Token>& tokens, uint32_t& tokenIndex)
{
	PPC::AST::FirstPass::ASTFirstPass_Node node;
	node.type = PPC::AST::FirstPass::ASTFirstPass_NodeType::ObjectStart;

	//gets name
	tokenIndex++;
	node.tokens.emplace_back(tokens[tokenIndex]);

	return node;
}

//creates a object end token
static inline PPC::AST::FirstPass::ASTFirstPass_Node ASTNodeCreate_ObjectEnd(const size_t& tokenCount, const std::vector<PPC::Token::Token>& tokens, uint32_t& tokenIndex)
{
	PPC::AST::FirstPass::ASTFirstPass_Node node;
	node.type = PPC::AST::FirstPass::ASTFirstPass_NodeType::ObjectEnd;

	return node;
}

//generates a first pass AST Tree
std::vector<PPC::AST::FirstPass::ASTFirstPass_Node> PPC::AST::FirstPass::GenerateFirstPassASTTree(const std::vector<Token::Token>& tokens)
{
	std::vector<PPC::AST::FirstPass::ASTFirstPass_Node> tree; tree.reserve(10);

	const size_t tokenCount = tokens.size();
	for (uint32_t i = 0; i < tokenCount; ++i)
	{
		//if it's a directive
		if (tokens[i].type == Token::TokenType::DotDirective)
		{
			//function start
			if (tokens[i].directiveMetadata.directive == Util::DotDirective::FuncStart)
				tree.emplace_back(ASTNodeCreate_FunctionStart(tokenCount, tokens, i));

			//function end
			else if (tokens[i].directiveMetadata.directive == Util::DotDirective::FuncEnd)
				tree.emplace_back(ASTNodeCreate_FunctionEnd(tokenCount, tokens, i));

			//object start
			else if (tokens[i].directiveMetadata.directive == Util::DotDirective::ObjectStart)
				tree.emplace_back(ASTNodeCreate_ObjectStart(tokenCount, tokens, i));

			//object end
			else if (tokens[i].directiveMetadata.directive == Util::DotDirective::ObjectEnd)
				tree.emplace_back(ASTNodeCreate_ObjectEnd(tokenCount, tokens, i));

			//jump definition inside a function
			else if (i + 1 < tokenCount && tokens[i + 1].type == PPC::Token::TokenType::Operator_Colon)
				tree.emplace_back(ASTNodeCreate_JumpLabel(tokenCount, tokens, i));
		}
		
		//variable inside a object/struct
		else if (tokens[i].type == PPC::Token::TokenType::DotDirective_Datatype)
			tree.emplace_back(ASTNodeCreate_Variable(tokenCount, tokens, i));
		
		//assembly instructions
		else if (tokens[i].type == PPC::Token::TokenType::Keyword_ASMInstruction)
			tree.emplace_back(ASTNodeCreate_AssemblyInstruction(tokenCount, tokens, i));
	}

	return tree;
}
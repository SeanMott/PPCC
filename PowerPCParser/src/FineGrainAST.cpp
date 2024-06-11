#include <PowerPCParser/FineGrainAST/FineGrainAST.hpp>

//creates a AST second pass node for a assembly instruction
static inline PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction CreateSecondPassASTNode_ASMInstruction(const std::vector<PPC::AST::FirstPass::ASTFirstPass_Node>& firstPassTree,
	const size_t& firstPassTreeCount, uint32& treeIndex)
{
	PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction node;
	
	//stores instruction
	node.opcode = firstPassTree[treeIndex].tokens[0].ASMInstructionMetadata;
	//node.instructionStr = firstPassTree[treeIndex].tokens[0].data;
	//node.instruction = firstPassTree[treeIndex].tokens[0].ASMInstructionMetadata.instruction;

	//pass in the parameters
	node.parameterTokens = firstPassTree[treeIndex].tokens;
	node.parameterTokens.erase(node.parameterTokens.begin()); //erase the first token since that stores the assembly instruction and this is supposed to parameters

	return node;
}

//creates a ast second pass node for jump labels
static inline PPC::AST::SecondPass::ASTSecondPass_Node_JumpLabel CreateSecondPassASTNode_JumpLabel(const std::vector<PPC::AST::FirstPass::ASTFirstPass_Node>& firstPassTree,
	const size_t& firstPassTreeCount, uint32& treeIndex)
{
	PPC::AST::SecondPass::ASTSecondPass_Node_JumpLabel node;

	//gets the name
	node.labelName = firstPassTree[treeIndex].tokens[0].data;

	//goes untill the end of the function
	treeIndex++;
	while (firstPassTree[treeIndex].type != PPC::AST::FirstPass::ASTFirstPass_NodeType::FunctionEnd && firstPassTree[treeIndex].type != PPC::AST::FirstPass::ASTFirstPass_NodeType::JumpLabel)
	{
		//parses the ASM instruction
		if (firstPassTree[treeIndex].type == PPC::AST::FirstPass::ASTFirstPass_NodeType::AssemblyInstruction)
			node.instructions.emplace_back(CreateSecondPassASTNode_ASMInstruction(firstPassTree, firstPassTreeCount, treeIndex));
	
		treeIndex++;
	}

	return node;
}

//creates a ast second pass node for functions
static inline PPC::AST::SecondPass::ASTSecondPass_Node CreateSecondPassASTNode_Function(const std::vector<PPC::AST::FirstPass::ASTFirstPass_Node>& firstPassTree,
	const size_t& firstPassTreeCount, uint32& treeIndex)
{
	PPC::AST::SecondPass::ASTSecondPass_Node node;
	node.type = PPC::AST::SecondPass::ASTSecondPass_NodeType::Function;

	//gets the name
	node.functionMetaData.funcName = firstPassTree[treeIndex].tokens[0].data;

	//goes untill the end of the function
	while (firstPassTree[treeIndex].type != PPC::AST::FirstPass::ASTFirstPass_NodeType::FunctionEnd)
	{
		treeIndex++;

		//parses the ASM instruction
		if (firstPassTree[treeIndex].type == PPC::AST::FirstPass::ASTFirstPass_NodeType::AssemblyInstruction)
			node.functionMetaData.instructions.emplace_back(CreateSecondPassASTNode_ASMInstruction(firstPassTree, firstPassTreeCount, treeIndex));

		//parses a jump label
		else if (firstPassTree[treeIndex].type == PPC::AST::FirstPass::ASTFirstPass_NodeType::JumpLabel)
			node.functionMetaData.jumpLabels.emplace_back(CreateSecondPassASTNode_JumpLabel(firstPassTree, firstPassTreeCount, treeIndex));
	}

	return node;
}

//creates a AST second pass node for a variables
static inline PPC::AST::SecondPass::ASTSecondPass_Node_Variable CreateSecondPassASTNode_Variable(const std::vector<PPC::AST::FirstPass::ASTFirstPass_Node>& firstPassTree,
	const size_t& firstPassTreeCount, uint32& treeIndex)
{
	PPC::AST::SecondPass::ASTSecondPass_Node_Variable node;
	node.tokens = firstPassTree[treeIndex].tokens; //takes in the tokens

	return node;
}

//creates a ast second pass node for objects
static inline PPC::AST::SecondPass::ASTSecondPass_Node CreateSecondPassASTNode_Object(const std::vector<PPC::AST::FirstPass::ASTFirstPass_Node>& firstPassTree,
	const size_t& firstPassTreeCount, uint32& treeIndex)
{
	PPC::AST::SecondPass::ASTSecondPass_Node node;
	node.type = PPC::AST::SecondPass::ASTSecondPass_NodeType::Object;

	//gets the name
	node.objMetaData.objName = firstPassTree[treeIndex].tokens[0].data;

	//goes untill the end of the function
	while (firstPassTree[treeIndex].type != PPC::AST::FirstPass::ASTFirstPass_NodeType::ObjectEnd)
	{
		treeIndex++;

		//parses the variable
		if (firstPassTree[treeIndex].type == PPC::AST::FirstPass::ASTFirstPass_NodeType::Variable)
			node.objMetaData.variables.emplace_back(CreateSecondPassASTNode_Variable(firstPassTree, firstPassTreeCount, treeIndex));
	}

	return node;
}

//generates the second pass of the AST tree
std::vector<PPC::AST::SecondPass::ASTSecondPass_Node> PPC::AST::SecondPass::GenerateSecondPassASTTree(const std::vector<PPC::AST::FirstPass::ASTFirstPass_Node>& firstPassTree)
{
	const size_t firstPassTreeCount = firstPassTree.size();
	std::vector<PPC::AST::SecondPass::ASTSecondPass_Node> tree; tree.reserve(firstPassTreeCount);

	//goes through the first pass
	for (uint32 i = 0; i < firstPassTreeCount; ++i)
	{
		//if it's a function start
		if (firstPassTree[i].type == FirstPass::ASTFirstPass_NodeType::FunctionStart)
			tree.emplace_back(CreateSecondPassASTNode_Function(firstPassTree, firstPassTreeCount, i));

		//if it's a object start
		else if (firstPassTree[i].type == FirstPass::ASTFirstPass_NodeType::ObjectStart)
			tree.emplace_back(CreateSecondPassASTNode_Object(firstPassTree, firstPassTreeCount, i));
	}

	return tree;
}
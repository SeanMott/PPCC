#include <PowerPCParser/CppCodeGen/CppCodeGen.hpp>

//converts a ASM instruction into a comment
static inline PPC::Backend::CppCodeGen::CodeGenNode CodeGen_ProcessASMInstructionIntoComment(const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
{
	//process ASM instructions into comment
	PPC::Backend::CppCodeGen::CodeGenNode node;

	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Comment;

	node.generalStrData = ASMInstruction->opcode.instructionStr + " ";

	for (uint32 t = 0; t < ASMInstruction->parameterTokens.size(); ++t)
		node.generalStrData += ASMInstruction->parameterTokens[t].data + " ";

	return node;
}

//processes a jump instruction
static inline bool CodeGen_ProcessASMInstruction_Jump(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;

	switch (ASMInstruction->opcode.instruction)
	{
		//blr
	case PPC::Decoder::ASM::eInstruction_blr:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
		node.generalStrData = "\treturn;"; //return control flow
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//b
	case PPC::Decoder::ASM::eInstruction_b:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
		node.generalStrData = "\tPPC::StaticRecompile::ASM::B_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //goto the label address
		node.generalStrData += "//" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + "\n"; //generates comment
		nodeExists = true;
		break;

		//bl
	case PPC::Decoder::ASM::eInstruction_bl:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
		node.generalStrData = "\tPPC::StaticRecompile::ASM::BL_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //goto the label address
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + "\n"; //generates comment
		nodeExists = true;
		break;

		//beq
	case PPC::Decoder::ASM::eInstruction_beq:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
		node.generalStrData = "\tPPC::StaticRecompile::ASM::BEQ_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //if equal to branch
		node.generalStrData += "//" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + "\n"; //generates comment
		nodeExists = true;
		break;

		//bne
	case PPC::Decoder::ASM::eInstruction_bne:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
		node.generalStrData = "\tPPC::StaticRecompile::ASM::BNE_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //if NOT equal to branch
		node.generalStrData += "//" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + "\n"; //generates comment
		nodeExists = true;
		break;

		//bctrl
	case PPC::Decoder::ASM::eInstruction_bctrl:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
		node.generalStrData = "\tPPC::StaticRecompile::ASM::BCTR(ctx);"; //if NOT equal to branch
		node.generalStrData += "//" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + " branch to the Count Register\n"; //generates comment
		nodeExists = true;
		break;

	}

	if(nodeExists)
		codeGenTree->emplace_back(node); //adds node

	return nodeExists;
}

//processes a store instruction
static inline bool CodeGen_ProcessASMInstruction_Store(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;

	switch (ASMInstruction->opcode.instruction)
	{
		//stwu
	case PPC::Decoder::ASM::eInstruction_stwu:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::STWU(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//stw
	case PPC::Decoder::ASM::eInstruction_stw:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::STW(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + 
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//stbu
	case PPC::Decoder::ASM::eInstruction_stbu:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::STBU(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;
	}
	
	if (nodeExists)
		codeGenTree->emplace_back(node); //adds node

	return nodeExists;
}

//processes a load instruction
static inline bool CodeGen_ProcessASMInstruction_Load(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;

	switch (ASMInstruction->opcode.instruction)
	{
		//lwz
	case PPC::Decoder::ASM::eInstruction_lwz:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::LWZ(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//lbzu
	case PPC::Decoder::ASM::eInstruction_lbzu:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::LBZU(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//li
	case PPC::Decoder::ASM::eInstruction_li:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::LI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//lis
	case PPC::Decoder::ASM::eInstruction_lis:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::LIS(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;
	}

	if (nodeExists)
		codeGenTree->emplace_back(node); //adds node

	return nodeExists;
}

//processes a move instruction
static inline bool CodeGen_ProcessASMInstruction_Move(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;

	switch (ASMInstruction->opcode.instruction)
	{
		//mflr
	case PPC::Decoder::ASM::eInstruction_mflr:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\t" + ASMInstruction->parameterTokens[0].data + " = ctx->LinkRegister;"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//mtlr
	case PPC::Decoder::ASM::eInstruction_mtlr:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tctx->LinkRegister = " + ASMInstruction->parameterTokens[0].data + ";"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//mr
	case PPC::Decoder::ASM::eInstruction_mr:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::MR(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//mtctr
	case PPC::Decoder::ASM::eInstruction_mtctr:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tctx->CountRegister = " + ASMInstruction->parameterTokens[0].data + ";"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;
	}

	if (nodeExists)
		codeGenTree->emplace_back(node); //adds node

	return nodeExists;
}

//processes a math instruction
static inline bool CodeGen_ProcessASMInstruction_Math(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;

	switch (ASMInstruction->opcode.instruction)
	{
		//add
	case PPC::Decoder::ASM::eInstruction_add:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::ADD(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//addi
	case PPC::Decoder::ASM::eInstruction_addi:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::ADDI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//subi
	case PPC::Decoder::ASM::eInstruction_subi:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::SUBI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//subf
	case PPC::Decoder::ASM::eInstruction_subf:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::SUBF(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//subic
	case PPC::Decoder::ASM::eInstruction_subic:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::SUBIC(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;
	}

	if (nodeExists)
		codeGenTree->emplace_back(node); //adds node

	return nodeExists;
}

//processes a compare instruction
static inline bool CodeGen_ProcessASMInstruction_Compare(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;

	switch (ASMInstruction->opcode.instruction)
	{
		//cmpwi
	case PPC::Decoder::ASM::eInstruction_cmpwi:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::CMPWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//cmplwi
	case PPC::Decoder::ASM::eInstruction_cmplwi:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::CMPLWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//cmplw
	case PPC::Decoder::ASM::eInstruction_cmplw:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::CMPLW(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;
	}

	if (nodeExists)
		codeGenTree->emplace_back(node); //adds node

	return nodeExists;
}

//process a bitshift instruction
static inline bool CodeGen_ProcessASMInstruction_Bitshift(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;

	switch (ASMInstruction->opcode.instruction)
	{
		//clrlwi
	case PPC::Decoder::ASM::eInstruction_clrlwi:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::CLRLWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + 
			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//or
	case PPC::Decoder::ASM::eInstruction_or:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
	
		node.generalStrData = "\tPPC::StaticRecompile::ASM::OR(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//nor
	case PPC::Decoder::ASM::eInstruction_nor:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
		
		node.generalStrData = "\tPPC::StaticRecompile::ASM::NOR(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//slwi
	case PPC::Decoder::ASM::eInstruction_slwi:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
		
		node.generalStrData = "\tPPC::StaticRecompile::ASM::SLWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//srwi
	case PPC::Decoder::ASM::eInstruction_srwi:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::SRWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;

		//ori
	case PPC::Decoder::ASM::eInstruction_ori:
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;

		node.generalStrData = "\tPPC::StaticRecompile::ASM::ORI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
		nodeExists = true;
		break;
	}

	if (nodeExists)
		codeGenTree->emplace_back(node); //adds node

	return nodeExists;
}

//processes a assembly instruction into a series of nodes
static inline void CodeGen_ProcessASMInstructionASTNode(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	uint32& ASMInstructionIndex,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction, 
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* peekNextInstruction)
{
	//Code Gen
	bool cCodeGenerated = CodeGen_ProcessASMInstruction_Jump(codeGenTree, ASMInstruction);
	if (!cCodeGenerated)
		cCodeGenerated = CodeGen_ProcessASMInstruction_Store(codeGenTree, ASMInstruction);
	if (!cCodeGenerated)
		cCodeGenerated = CodeGen_ProcessASMInstruction_Move(codeGenTree, ASMInstruction);
	if (!cCodeGenerated)
		cCodeGenerated = CodeGen_ProcessASMInstruction_Load(codeGenTree, ASMInstruction);
	if (!cCodeGenerated)
		cCodeGenerated = CodeGen_ProcessASMInstruction_Math(codeGenTree, ASMInstruction);
	if (!cCodeGenerated)
		cCodeGenerated = CodeGen_ProcessASMInstruction_Compare(codeGenTree, ASMInstruction);
	if (!cCodeGenerated)
		cCodeGenerated = CodeGen_ProcessASMInstruction_Bitshift(codeGenTree, ASMInstruction);

	//process ASM instructions into comment
	if (!cCodeGenerated)
		codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));
}

//processes a function into a series of nodes
static inline void CodeGen_ProcessFunctionASTNode(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node* secondPassASTTree, uint32& ASTTreeIndex, const size_t& ASTTreeLength)
{
	//generate the prototype
	PPC::Backend::CppCodeGen::CodeGenNode node;
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::FunctionPrototype;
	node.functionMetadata.funcName = secondPassASTTree[ASTTreeIndex].functionMetaData.funcName;
	codeGenTree->emplace_back(node);

	//adds {
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Operator_Curly_Bracket_Open;
	node.generalStrData = "{";
	codeGenTree->emplace_back(node);
	
	//processes ASM Instructions
	size_t instructionCount = secondPassASTTree[ASTTreeIndex].functionMetaData.instructions.size();
	for (uint32 i = 0; i < instructionCount; ++i)
		CodeGen_ProcessASMInstructionASTNode(codeGenTree, i,
			&secondPassASTTree[ASTTreeIndex].functionMetaData.instructions[i],
			(i + 1 < instructionCount ? &secondPassASTTree[ASTTreeIndex].functionMetaData.instructions[i + 1] : nullptr));

	//process jump labels
	for (uint32 i = 0; i < secondPassASTTree[ASTTreeIndex].functionMetaData.jumpLabels.size(); ++i)
	{
		//adds label
		const PPC::AST::SecondPass::ASTSecondPass_Node_JumpLabel jumpLabel = secondPassASTTree[ASTTreeIndex].functionMetaData.jumpLabels[i];
		node.generalStrData = jumpLabel.labelName;
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::JumpLabel;
		codeGenTree->emplace_back(node);
		
		//process the label's instructions
		instructionCount = jumpLabel.instructions.size();
		for (uint32 t = 0; t < instructionCount; ++t)
			CodeGen_ProcessASMInstructionASTNode(codeGenTree, i,
				&jumpLabel.instructions[t],
				(t + 1 < instructionCount ? &jumpLabel.instructions[t + 1] : nullptr));
	}

	//adds }
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Operator_Curly_Bracket_Closed;
	node.generalStrData = "}";
	codeGenTree->emplace_back(node);
}

//processes a object into a series of nodes
static inline void CodeGen_ProcessObjectASTNode(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	const PPC::AST::SecondPass::ASTSecondPass_Node* secondPassASTTree, uint32& ASTTreeIndex, const size_t& ASTTreeLength)
{
	PPC::AST::SecondPass::ASTSecondPass_Node secondASTNode = secondPassASTTree[ASTTreeIndex];

	//generate the prototype
	PPC::Backend::CppCodeGen::CodeGenNode node;
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::ObjectPrototype;
	node.objectMetadata.objName = secondASTNode.objMetaData.objName;
	codeGenTree->emplace_back(node);

	//adds {
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Operator_Curly_Bracket_Open;
	node.generalStrData = "{";
	codeGenTree->emplace_back(node);

	//processes variables
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
	for (uint32 i = 0; i < secondASTNode.objMetaData.variables.size(); ++i)
	{
		//process the datatype
		switch (secondASTNode.objMetaData.variables[i].tokens[0].datatypeMetadata.datatype)
		{
		case PPC::Util::Datatype::Skip_Uint16:
			node.generalStrData = "uint16";
			break;
		case PPC::Util::Datatype::Byte:
			node.generalStrData = "uint8";
			break;
		case PPC::Util::Datatype::Byte_4:
			
			//if it's a hex value
			if (secondASTNode.objMetaData.variables[i].tokens[1].type == PPC::Token::TokenType::Literal_HexValue)
				node.generalStrData = "uint32";
			//if it's a function pointer
			else
				node.generalStrData = "void*";
			
			break;
		case PPC::Util::Datatype::Float:
			node.generalStrData = "float";
			break;
		case PPC::Util::Datatype::Double:
			node.generalStrData = "double";
			break;

		default:
			node.generalStrData = "WE_DON'T_PROCESS_THIS_VARIABLE_DATATYPE_IN_THE_C_GEN_THIS_IS_A_BUG";	
			break;

		}

		//appends name
		node.generalStrData += " variableData" + std::to_string(i) + " = ";

		//sets value
		node.generalStrData += secondASTNode.objMetaData.variables[i].tokens[1].data + ";";

		//adds the node
		codeGenTree->emplace_back(node);
	}

	//adds }
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Operator_Curly_Bracket_Closed;
	node.generalStrData = "}";
	codeGenTree->emplace_back(node);
}

//generates C++ code bits from fine-grain AST
std::vector<PPC::Backend::CppCodeGen::CodeGenNode> PPC::Backend::CppCodeGen::RunCodeGen(const std::vector<PPC::AST::SecondPass::ASTSecondPass_Node>& secondPassASTTree)
{
	std::vector<PPC::Backend::CppCodeGen::CodeGenNode> codeGenTree;

	//goes through the AST tree
	const size_t ASTTreeLength = secondPassASTTree.size();
	for (uint32 i = 0; i < ASTTreeLength; ++i)
	{
		//processes a function
		if (secondPassASTTree[i].type == PPC::AST::SecondPass::ASTSecondPass_NodeType::Function)
			CodeGen_ProcessFunctionASTNode(&codeGenTree, secondPassASTTree.data(), i, ASTTreeLength);

		//processes a object
		else if (secondPassASTTree[i].type == PPC::AST::SecondPass::ASTSecondPass_NodeType::Object)
			CodeGen_ProcessObjectASTNode(&codeGenTree, secondPassASTTree.data(), i, ASTTreeLength);
	}

	return codeGenTree;
}
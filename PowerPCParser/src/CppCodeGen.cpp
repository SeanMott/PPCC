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

////processes a jump instruction
//static inline bool CodeGen_ProcessASMInstruction_Jump(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
//	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
//{
//	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;
//
//	switch (ASMInstruction->opcode.instruction)
//	{
//		//blr
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_blr:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//		node.generalStrData = "\treturn;"; //return control flow
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//b
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_b:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::B_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //goto the label address
//		node.generalStrData += "//" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + "\n"; //generates comment
//		nodeExists = true;
//		break;
//
//		//bl
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_bl:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::BL_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //goto the label address
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + "\n"; //generates comment
//		nodeExists = true;
//		break;
//
//		//beq
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_beq:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::BEQ_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //if equal to branch
//		node.generalStrData += "//" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + "\n"; //generates comment
//		nodeExists = true;
//		break;
//
//		//bne
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_bne:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::BNE_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //if NOT equal to branch
//		node.generalStrData += "//" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + "\n"; //generates comment
//		nodeExists = true;
//		break;
//
//		//bctrl
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_bctrl:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::BCTR(ctx);"; //if NOT equal to branch
//		node.generalStrData += "//" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData + " branch to the Count Register\n"; //generates comment
//		nodeExists = true;
//		break;
//
//	}
//
//	if (nodeExists)
//		codeGenTree->emplace_back(node); //adds node
//
//	return nodeExists;
//}

////processes a store instruction
//static inline bool CodeGen_ProcessASMInstruction_Store(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
//	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
//{
//	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;
//
//	switch (ASMInstruction->opcode.instruction)
//	{
//		//stwu
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_stwu:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::STWU(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
//			", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//stw
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_stw:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::STW(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//stbu
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_stbu:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::STBU(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//	}
//
//	if (nodeExists)
//		codeGenTree->emplace_back(node); //adds node
//
//	return nodeExists;
//}

////processes a load instruction
//static inline bool CodeGen_ProcessASMInstruction_Load(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
//	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
//{
//	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;
//
//	switch (ASMInstruction->opcode.instruction)
//	{
//		//lwz
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_lwz:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::LWZ(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//lbzu
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_lbzu:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::LBZU(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//li
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_li:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::LI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//lis
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_lis:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::LIS(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//	}
//
//	if (nodeExists)
//		codeGenTree->emplace_back(node); //adds node
//
//	return nodeExists;
//}

////processes a move instruction
//static inline bool CodeGen_ProcessASMInstruction_Move(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
//	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
//{
//	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;
//
//	switch (ASMInstruction->opcode.instruction)
//	{
//		//mflr
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_mflr:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\t" + ASMInstruction->parameterTokens[0].data + " = ctx->LinkRegister;"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//mtlr
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_mtlr:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tctx->LinkRegister = " + ASMInstruction->parameterTokens[0].data + ";"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//mr
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_mr:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::MR(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//mtctr
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_mtctr:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tctx->CountRegister = " + ASMInstruction->parameterTokens[0].data + ";"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//	}
//
//	if (nodeExists)
//		codeGenTree->emplace_back(node); //adds node
//
//	return nodeExists;
//}

////processes a math instruction
//static inline bool CodeGen_ProcessASMInstruction_Math(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
//	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
//{
//	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;
//
//	switch (ASMInstruction->opcode.instruction)
//	{
//		//add
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_add:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::ADD(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//addi
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_addi:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::ADDI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//subi
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_subi:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::SUBI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//subf
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_subf:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::SUBF(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//subic
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_subic:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::SUBIC(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//	}
//
//	if (nodeExists)
//		codeGenTree->emplace_back(node); //adds node
//
//	return nodeExists;
//}

////processes a compare instruction
//static inline bool CodeGen_ProcessASMInstruction_Compare(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
//	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
//{
//	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;
//
//	switch (ASMInstruction->opcode.instruction)
//	{
//		//cmpwi
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_cmpwi:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::CMPWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//cmplwi
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_cmplwi:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::CMPLWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//cmplw
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_cmplw:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::CMPLW(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//	}
//
//	if (nodeExists)
//		codeGenTree->emplace_back(node); //adds node
//
//	return nodeExists;
//}

////process a bitshift instruction
//static inline bool CodeGen_ProcessASMInstruction_Bitshift(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
//	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction)
//{
//	PPC::Backend::CppCodeGen::CodeGenNode node; bool nodeExists = false;
//
//	switch (ASMInstruction->opcode.instruction)
//	{
//		//clrlwi
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_clrlwi:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::CLRLWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
//			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//or
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_or:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::OR(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
//			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//nor
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_nor:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::NOR(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
//			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//slwi
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_slwi:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::SLWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
//			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//srwi
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_srwi:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::SRWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
//			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//
//		//ori
//	case PPC::PPC::Decoder::ASM::case PPC::Decoder::ASM::EInstruction::eInstruction_ori:
//		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
//
//		node.generalStrData = "\tPPC::StaticRecompile::ASM::ORI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
//			", " + ASMInstruction->parameterTokens[2].data + "); "; //sets data
//		node.generalStrData += " //" + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //generates comment
//		nodeExists = true;
//		break;
//	}
//
//	if (nodeExists)
//		codeGenTree->emplace_back(node); //adds node
//
//	return nodeExists;
//}

//processes a assembly instruction into a series of nodes
static inline void CodeGen_ProcessASMInstructionASTNode(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	uint32& ASMInstructionIndex,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* peekNextInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode codeGenNode;

	switch (ASMInstruction->opcode.instruction)
	{
	case PPC::Decoder::ASM::EInstruction::eInstruction_nop:
		codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));
		break;

		// move register (with move to/from special registers)
	case PPC::Decoder::ASM::EInstruction::eInstruction_mr:
		codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));
		break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfspr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfsprg:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfsrr0:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfsrr1:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtspr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfmsr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtsrr0:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtsrr1:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtsprg:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfmsrg:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtmsr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtdar:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtdsisr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtmsrd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtmsree:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtxer:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfcr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtcrf:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfocrf:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtocrf:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mcrf:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mftb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mflr:
		codeGenNode.generalStrData = "\tctx.GPR.GPR[" + ASMInstruction->parameterTokens[0].data + "] = ctx.SPR.LR;"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;
	
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtctr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfdar:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// load memory

	case PPC::Decoder::ASM::EInstruction::eInstruction_lbz:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhz:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LHZ(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lwz:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LWZ(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lbzu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhzu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwzu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lba:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lha:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwa:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbau:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhau:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwau:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ld:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ldu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lmw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// load memory indexed
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbzx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhzx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwzx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbzux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhzux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwzux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbax:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhax:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwax:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbaux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhaux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwaux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ldx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ldux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	
		// store memory
	case PPC::Decoder::ASM::EInstruction::eInstruction_stb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sth:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stw:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STW(ctx.GPR.GPR, ctx.GPR.GPR[" + ASMInstruction->parameterTokens[0].data + "], " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ", ctx.memory); "; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_std:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_slwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stbu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sthu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwu:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STWU(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + "); "; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_stdu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

	// store memory indexed
	case PPC::Decoder::ASM::EInstruction::eInstruction_stbx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sthx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stdx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stbux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sthux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stdux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

	//quantized store
	case PPC::Decoder::ASM::EInstruction::eInstruction_psq_stx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_psq_lx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_psq_st:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_psq_l:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		//idk
	case PPC::Decoder::ASM::EInstruction::eInstruction_twui:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// branch instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_b:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bdnz:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ba:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bl:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::BL_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_blt:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bla:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bcl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bca:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bcla:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bclr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bclrl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bcctr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bcctrl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_beq:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_beq_plus:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_beqlr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_blr:
		codeGenNode.generalStrData = "\treturn;"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bltlr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bne:
		codeGenNode.generalStrData = "\tif(PPC::StaticRecompile::ASM::BNE_If(ctx))"; //if check
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM	
		
		//body of if so we can actually jump to the address
		codeGenNode.generalStrData += "\n\t{\n\t\tgoto " + ASMInstruction->parameterTokens[0].data + ";\n\t}\n";
		
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bnelr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bge:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bgelr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bgt:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bctr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bctrl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

	 // lwarx/stwcx
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwarx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ldarx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwcx_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break; //.
	case PPC::Decoder::ASM::EInstruction::eInstruction_stdcx_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break; //.

		// memory bariers
	case PPC::Decoder::ASM::EInstruction::eInstruction_isync:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sync:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwsync:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ptesync:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_eieio:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// custom
	//case PPC::Decoder::ASM::EInstruction::eInstruction_cmp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fcmpu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fcmpo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_twi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_tdi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_tw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_td:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// generic instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_sc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// condition register operators
	case PPC::Decoder::ASM::EInstruction::eInstruction_crand:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cror:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crxor:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crnand:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crnor:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_creqv:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crandc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crorc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crclr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// load immediate
	case PPC::Decoder::ASM::EInstruction::eInstruction_li:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lis:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LIS(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

		// math with immediate value
	case PPC::Decoder::ASM::EInstruction::eInstruction_addic:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addic_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addi:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ADDI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_addis:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfic:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulli:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// add XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_add:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_add_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// subtract grom XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subic:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subf:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subf_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// add carrying XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_addc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addc_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addco:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addco_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// subtract From carrying XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfc_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfco:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfco_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// add extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_adde:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_adde_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addeo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addeo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// subtract from extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfe:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfe_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfeo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfeo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subis:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// add to minus one extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_addme:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addme_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addmeo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addmeo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// subtract from minus one extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfme:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfme_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfmeo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfmeo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// add to zero extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_addze:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addze_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addzeo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addzeo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// subtract from zero extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfze:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfze_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfzeo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfzeo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// negate
	case PPC::Decoder::ASM::EInstruction::eInstruction_neg:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_neg_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_nego:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_nego_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// multiply low doubleword XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulld:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulld_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulldo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulldo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// multiply low word XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullwo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullwo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// multiply high doubleword XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullhd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullhd_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// multiply High Word XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullhw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullhw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// multiply high doubleword unsigned XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulhdu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulhdu_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// multiply High Word Unsigned XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulhwu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulhwu_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// divide doubleword XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_divd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divd_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divdo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divdo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// divide word XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_divw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// divide doubleword unsigned XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_divdu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divdu_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divduo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divduo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// divide word unsigned XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwu_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwuo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwuo_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// compare
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpwi:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::CMPWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpdi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmplwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpldi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmplw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpld:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

	// logical instructions with immediate values
	case PPC::Decoder::ASM::EInstruction::eInstruction_andi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_andis:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_andi_Dot:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ANDI_DOT(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_andis_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ori:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_oris:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_xori:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_xoris:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// logical instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_and:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_and_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_or:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_or_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_xor:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_xor_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_nand:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_nand_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_nor:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_nor_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_eqv:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_eqv_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_andc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_andc_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_orc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_orc_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	
	// byte extend
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsb_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsh_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extrwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// population count
	case PPC::Decoder::ASM::EInstruction::eInstruction_popcntb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cntlzw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cntlzw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cntlzd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cntlzd_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

	// Shift instructions with immediate params -->
	// REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldicl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldicl_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldicr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldicr_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldic:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldic_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldimi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldimi_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_clrlwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_clrrwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_clrlslwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwinm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwinm_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwimi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwimi_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldcl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldcl_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldcr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldcr_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwnm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwnm_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Extended shifts
	case PPC::Decoder::ASM::EInstruction::eInstruction_sld:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sld_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_slw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_slw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srd_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srad:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srad_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sraw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sraw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Extended shifts with immediate... geez..
	case PPC::Decoder::ASM::EInstruction::eInstruction_srawi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srawi_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sradi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sradi_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Cache operation instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbf:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbst:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbt:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbtst:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbz:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		//  Floating point load instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfsu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfsx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfsux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfdu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfdx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfdux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		//  Floating point store instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfsu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfsx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfsux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfdu:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfdx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfdux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Store float point as integer word indexed
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfiwx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		//store move register
	case PPC::Decoder::ASM::EInstruction::eInstruction_stmw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Floating point move and single op instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmr_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fneg:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fneg_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fabs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fabs_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnabs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnabs_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Floating point arithmetic instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_fadd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fadd_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fadds:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fadds_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsub:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsub_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsubs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsubs_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmul:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmul_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmuls:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmuls_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fdiv:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fdiv_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fdivs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fdivs_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsqrt:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsqrt_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsqrtx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsqrtx_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsqrte:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fre:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fre_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Floating point mad instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmadd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmadd_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmadds:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmadds_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmsub:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmsub_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmsubs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmsubs_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmadd:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmadd_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmadds:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmadds_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmsub:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmsub_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmsubs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmsubs_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Floating point rounding and conversion
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsp_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctid:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctid_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctidz:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctidz_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctiw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctiw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctiwz:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctiwz_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fcfid:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fcfid_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Floating point select
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsel:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsel_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

		// Floating point control registers
	case PPC::Decoder::ASM::EInstruction::eInstruction_mffs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mffs_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mcrfs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsfi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsfi_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsf:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsf_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsb0:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsb0_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsb1:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsb1_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtlr:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::MTLR(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenTree->emplace_back(codeGenNode);
		break;

		// VMX instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvebx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvehx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvewx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvlx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvlxl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvrx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvrxl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvsl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvsr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;			//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvxl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfvscr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtvscr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvebx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvehx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvewx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvlx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvlxl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvrx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvrxl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvxl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhbrx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwbrx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sthbrx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwbrx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lswi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lswx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stswi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stswx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddcuw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddsbs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddshs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddsws:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddubm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddubs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vadduhm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vadduhs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vadduwm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vadduws:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vand:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vandc:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavgsb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavgsh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavgsw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavgub:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavguh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavguw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcfpsxws:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcfpuxws:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcsxwfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break; //+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcuxwfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break; //+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vctsxs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vctuxs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcfsx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcfux:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpbfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpbfp_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpeqfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpeqfp_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequb_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequh_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgefp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgefp_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtfp_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsb_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsh_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtub:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtub_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtuh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtuh_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtuw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtuw_Dot:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vexptefp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vlogefp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaddcfp128:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaddfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxsb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxsh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxsw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxub:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxuh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxuw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminsb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminsh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminsw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminub:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminuh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminuw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrghb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrghh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrghw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrglb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrglh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrglw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vdot3fp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vdot4fp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmulfp128:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vnmsubfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vnor:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vor:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;			//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vperm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpermwi128:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkd3d128:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkpx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkshss:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkshus:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkswss:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkswus:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkuhum:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkuhus:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkuwum:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkuwus:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrefp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_rfi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrfim:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrfin:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrfip:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrfiz:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrlb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrlh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrlimi128:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrlw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrsqrtefp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsel:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsl:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vslb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsldoi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vslh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vslo:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vslw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsplth:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltisb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltish:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltisw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsr:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrab:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrah:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsraw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsro:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubcuw:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubfp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubsbs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubshs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubsws:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsububm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsububs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubuhm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubuhs:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubuwm:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubuws:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupkd3d128:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupkhpx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupkhsb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupkhsh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupklpx:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupklsb:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupklsh:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vxor:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;		//+

		//extra
	case PPC::Decoder::ASM::EInstruction::eInstruction_icbi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rotlwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rotrwi:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;

	//catch all
	case PPC::Decoder::ASM::EInstruction::eInstruction_MAX:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
		default:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction)); break;
	}

	//Code Gen
	//bool cCodeGenerated = CodeGen_ProcessASMInstruction_Jump(codeGenTree, ASMInstruction);
	//if (!cCodeGenerated)
	//	cCodeGenerated = CodeGen_ProcessASMInstruction_Store(codeGenTree, ASMInstruction);
	//if (!cCodeGenerated)
	//	cCodeGenerated = CodeGen_ProcessASMInstruction_Move(codeGenTree, ASMInstruction);
	//if (!cCodeGenerated)
	//	cCodeGenerated = CodeGen_ProcessASMInstruction_Load(codeGenTree, ASMInstruction);
	//if (!cCodeGenerated)
	//	cCodeGenerated = CodeGen_ProcessASMInstruction_Math(codeGenTree, ASMInstruction);
	//if (!cCodeGenerated)
	//	cCodeGenerated = CodeGen_ProcessASMInstruction_Compare(codeGenTree, ASMInstruction);
	//if (!cCodeGenerated)
	//	cCodeGenerated = CodeGen_ProcessASMInstruction_Bitshift(codeGenTree, ASMInstruction);

	//process ASM instructions into comment
	//if (!cCodeGenerated)
	//	codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));
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

	//adds a "GameCube::GameCubeRegisters ctx;" context for registers
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::GenaricCodeLine;
	node.generalStrData = "\tGameCube::GameCubeRegisters ctx;\n";
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
std::vector<PPC::Backend::CppCodeGen::CodeGenNode> PPC::Backend::CppCodeGen::RunCodeGen(const std::vector<PPC::AST::SecondPass::ASTSecondPass_Node>& secondPassASTTree,
	const std::string& filename)
{
	std::vector<PPC::Backend::CppCodeGen::CodeGenNode> codeGenTree;
	const size_t ASTTreeLength = secondPassASTTree.size();
	codeGenTree.reserve(ASTTreeLength + 1);

	//adds includes at the top of the file
	PPC::Backend::CppCodeGen::CodeGenNode includeGen;
	includeGen.generalStrData = "#include \"includes/PPC/StaticRecompile/Macros.h\"\n#include \"includes/GameCubeRegisters.h\""; //static recomp includes
	includeGen.generalStrData += "\n#include \"CppCodeGenDump_" + filename + ".hpp\""; //header file of this file
	includeGen.generalStrData += "\n#include <iostream>\n\n"; //standard lib Cout	
	codeGenTree.emplace_back(includeGen);

	//goes through the AST tree
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
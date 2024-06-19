#include <PowerPCParser/CppCodeGen/CppCodeGen.hpp>

#include <PowerPCParser/CppMacroBlackMagic/Impls.hpp>

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

//processes a assembly instruction into a series of nodes
static inline void CodeGen_ProcessASMInstructionASTNode(std::vector<PPC::Backend::CppCodeGen::CodeGenNode>* codeGenTree,
	uint32& ASMInstructionIndex,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction,
	const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* peekNextInstruction)
{
	PPC::Backend::CppCodeGen::CodeGenNode codeGenNode;

	switch (ASMInstruction->opcode.instruction)
	{
	case PPC::Decoder::ASM::EInstruction::eInstruction_nop:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// move register (with move to/from special registers)
	case PPC::Decoder::ASM::EInstruction::eInstruction_mr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mfspr:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::MFSPR(ctx.GPR.GPR, ctx.SPR.SPR, " + ASMInstruction->parameterTokens[0].data + ", ctx.SPR.SPR);"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mfsprg:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mfsrr0:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mfsrr1:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mtspr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfmsr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mtsrr0:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mtsrr1:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mtsprg:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mfmsrg:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mtmsr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mtdar:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtdsisr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtmsrd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtmsree:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtxer:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfcr:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::MFCR(ctx.GRP.GRP, ctx.CR" + ASMInstruction->parameterTokens[0].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mtcrf:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mfocrf:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mtocrf:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mcrf:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mftb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mflr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtctr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_mfdar:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// load memory

	case PPC::Decoder::ASM::EInstruction::eInstruction_lbz:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LBZ(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lhz:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LHZ(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lwz:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LWZ(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lbzu:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LBZU(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lhzu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwzu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lba:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lha:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwa:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbau:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhau:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwau:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ld:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ldu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lmw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// load memory indexed
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbzx:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LBZX(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lhzx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwzx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbzux:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LBZUX(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lhzux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwzux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbax:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhax:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwax:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lbaux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhaux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwaux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ldx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ldux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	
		// store memory
	case PPC::Decoder::ASM::EInstruction::eInstruction_stb:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STB(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_sth:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STH(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + "); "; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_stw:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STW(ctx.GPR.GPR, ctx.GPR.GPR[" + ASMInstruction->parameterTokens[0].data + "], " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ", ctx.memory); "; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_std:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_slwi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_stbu:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STBU(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + "); "; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_sthu:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STHU(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + "); "; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_stwu:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STWU(ctx, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + "); "; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_stdu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	// store memory indexed
	case PPC::Decoder::ASM::EInstruction::eInstruction_stbx:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::STBX(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + "); "; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_sthx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stdx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stbux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sthux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stdux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	//quantized store
	case PPC::Decoder::ASM::EInstruction::eInstruction_psq_stx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_psq_lx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_psq_st:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_psq_l:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		//idk
	case PPC::Decoder::ASM::EInstruction::eInstruction_twui:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// branch instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_b:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::B(&ctx.PC, " + ASMInstruction->parameterTokens[0].data + ");"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bdnz:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_ba:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::BA(ctx.PC, " + ASMInstruction->parameterTokens[0].data + ");"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bl:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::BL_If(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_blt:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bla:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bc:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bcl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bca:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bcla:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bclr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bclrl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bcctr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bcctrl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_beq:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_beq_plus:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_beqlr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_blr:
		codeGenNode.generalStrData = "\treturn;"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bltlr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bne:
		codeGenNode.generalStrData = "\tif(PPC::StaticRecompile::ASM::BNE_If(ctx))"; //if check
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM	
		
		//body of if so we can actually jump to the address
		codeGenNode.generalStrData += "\n\t{\n\t\tgoto " + ASMInstruction->parameterTokens[0].data + ";\n\t}\n";
		
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bnelr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bge:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bgelr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bgt:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_bctr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_bctrl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	 // lwarx/stwcx
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwarx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_ldarx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwcx_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break; //.
	case PPC::Decoder::ASM::EInstruction::eInstruction_stdcx_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break; //.

		// memory bariers
	case PPC::Decoder::ASM::EInstruction::eInstruction_isync:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ISYNC();"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_sync:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::SYNC();"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lwsync:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LWSYNC();"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_ptesync:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_eieio:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::EIEIO();"; //C++ code
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

		// custom
	//case PPC::Decoder::ASM::EInstruction::eInstruction_cmp:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fcmpu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fcmpo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_twi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_tdi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_tw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_td:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// generic instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_sc:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// condition register operators
	case PPC::Decoder::ASM::EInstruction::eInstruction_crand:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cror:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crxor:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crnand:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crnor:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_creqv:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crandc:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crorc:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_crclr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// load immediate
	case PPC::Decoder::ASM::EInstruction::eInstruction_li:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_lis:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::LIS(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

		// math with immediate value
	case PPC::Decoder::ASM::EInstruction::eInstruction_addic:
		CPP_IMPL_CODE_GEN(PPC::StaticRecompile::ASM::CPP_FUNC_STR_ADDIC(ASMInstruction))
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_addic_Dot:
		CPP_IMPL_CODE_GEN(PPC::StaticRecompile::ASM::CPP_FUNC_STR_ADDIC_DOT(ASMInstruction))
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_addi:
		CPP_IMPL_CODE_GEN(PPC::StaticRecompile::ASM::CPP_FUNC_STR_ADDI(ASMInstruction))
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_addis:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfic:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulli:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// add XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_add:
		CPP_IMPL_CODE_GEN(PPC::StaticRecompile::ASM::CPP_FUNC_STR_ADD(ASMInstruction))
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_add_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_addo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_addo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// subtract grom XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_subic:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_subf:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::SUBF(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_subf_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// add carrying XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_addc:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addc_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addco:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addco_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// subtract From carrying XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfc:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfc_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfco:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfco_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// add extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_adde:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_adde_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addeo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addeo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// subtract from extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfe:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfe_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfeo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfeo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subis:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// add to minus one extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_addme:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addme_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addmeo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addmeo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// subtract from minus one extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfme:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfme_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfmeo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfmeo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// add to zero extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_addze:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addze_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addzeo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_addzeo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// subtract from zero extended XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfze:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfze_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfzeo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_subfzeo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// negate
	case PPC::Decoder::ASM::EInstruction::eInstruction_neg:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_neg_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_nego:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_nego_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// multiply low doubleword XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulld:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulld_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulldo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulldo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// multiply low word XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullwo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullwo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// multiply high doubleword XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullhd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullhd_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// multiply High Word XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullhw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mullhw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// multiply high doubleword unsigned XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulhdu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulhdu_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// multiply High Word Unsigned XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulhwu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mulhwu_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// divide doubleword XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_divd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divd_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divdo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divdo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// divide word XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_divw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// divide doubleword unsigned XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_divdu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divdu_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divduo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divduo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// divide word unsigned XO-form
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwu_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwuo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_divwuo_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// compare
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpwi:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::CMPWI(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpdi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmplwi:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::CMPLWI(ctx.GPR.GPR, &ctx.CR.CR, 0, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpldi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cmplw:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::CMPLW(ctx.GPR.GPR, &ctx.CR.CR, 0, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_cmpld:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	// logical instructions with immediate values
	case PPC::Decoder::ASM::EInstruction::eInstruction_andi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_andis:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_andi_Dot:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ANDI_DOT(ctx, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_andis_Dot:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ANDIS_DOT(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ", ctx.CR);"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_ori:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ORI(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_oris:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ORIS(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_xori:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::XORI(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_xoris:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::XORIS(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

		// logical instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_and:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::AND(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_and_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_or:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::OR(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_or_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_xor:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::XOR(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_xor_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_nand:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::NAND(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_nand_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_nor:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::NOR(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_nor_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_eqv:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::EQV(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_eqv_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_andc:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ANDC(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_andc_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_orc:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ORC(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data +
			", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_orc_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	
	// byte extend
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsb_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsh_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extsw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_extrwi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// population count
	case PPC::Decoder::ASM::EInstruction::eInstruction_popcntb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cntlzw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cntlzw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cntlzd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_cntlzd_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	// Shift instructions with immediate params -->
	// REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldicl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldicl_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldicr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldicr_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldic:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldic_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldimi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_rldimi_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_clrlwi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_clrrwi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_clrlslwi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwinm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwinm_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwimi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwimi_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldcl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldcl_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldcr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rldcr_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;REG:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM:codeGenTree->emplace_back(CodeGen_ProcessASMInstructionIntoComment(ASMInstruction));break;IMM
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwnm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_rlwnm_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Extended shifts
	case PPC::Decoder::ASM::EInstruction::eInstruction_sld:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sld_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_slw:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::SLW(ctx.GPR.GPR, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ", " + ASMInstruction->parameterTokens[2].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_slw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srd_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srwi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srad:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srad_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sraw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sraw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Extended shifts with immediate... geez..
	case PPC::Decoder::ASM::EInstruction::eInstruction_srawi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_srawi_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sradi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sradi_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Cache operation instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbi:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::DCBI(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbf:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::DCBF(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbst:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::DCBST(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " + ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbt:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbtst:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_dcbz:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		//  Floating point load instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfsu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfsx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfsux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfdu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfdx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lfdux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		//  Floating point store instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfsu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfsx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfsux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfdu:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfdx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfdux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Store float point as integer word indexed
	case PPC::Decoder::ASM::EInstruction::eInstruction_stfiwx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		//store move register
	case PPC::Decoder::ASM::EInstruction::eInstruction_stmw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Floating point move and single op instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmr_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fneg:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fneg_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fabs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fabs_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnabs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnabs_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Floating point arithmetic instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_fadd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fadd_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fadds:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fadds_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsub:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsub_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsubs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsubs_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmul:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmul_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmuls:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmuls_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fdiv:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fdiv_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fdivs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fdivs_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsqrt:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsqrt_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsqrtx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsqrtx_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsqrte:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fre:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fre_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Floating point mad instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmadd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmadd_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmadds:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmadds_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmsub:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmsub_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmsubs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fmsubs_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmadd:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmadd_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmadds:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmadds_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmsub:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmsub_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmsubs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fnmsubs_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Floating point rounding and conversion
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_frsp_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctid:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctid_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctidz:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctidz_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctiw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctiw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctiwz:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fctiwz_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fcfid:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fcfid_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Floating point select
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsel:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_fsel_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		// Floating point control registers
	case PPC::Decoder::ASM::EInstruction::eInstruction_mffs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mffs_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mcrfs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsfi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsfi_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsf:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsf_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsb0:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsb0_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsb1:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtfsb1_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtlr:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::MTLR(ctx, " + ASMInstruction->parameterTokens[0].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

		// VMX instructions
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvebx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvehx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvewx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvlx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvlxl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvrx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvrxl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvsl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvsr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;			//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lvxl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_mfvscr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_mtvscr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvebx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvehx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvewx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvlx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvlxl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvrx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvrxl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_stvxl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_lhbrx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lwbrx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_sthbrx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stwbrx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lswi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_lswx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stswi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_stswx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddcuw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddsbs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddshs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddsws:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddubm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vaddubs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vadduhm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vadduhs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vadduwm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vadduws:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vand:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vandc:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavgsb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavgsh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavgsw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavgub:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavguh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vavguw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcfpsxws:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcfpuxws:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcsxwfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break; //+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcuxwfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break; //+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vctsxs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vctuxs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcfsx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcfux:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpbfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpbfp_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpeqfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpeqfp_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequb_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequh_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpequw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgefp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgefp_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtfp_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsb_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsh_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtsw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtub:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtub_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtuh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtuh_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtuw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vcmpgtuw_Dot:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vexptefp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vlogefp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaddcfp128:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaddfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxsb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxsh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxsw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxub:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxuh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmaxuw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminsb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminsh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminsw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminub:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminuh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vminuw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrghb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrghh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrghw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrglb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrglh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmrglw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vdot3fp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vdot4fp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vmulfp128:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vnmsubfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vnor:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
		
	case PPC::Decoder::ASM::EInstruction::eInstruction_vor:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;			//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vperm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpermwi128:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkd3d128:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkpx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkshss:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkshus:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkswss:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkswus:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkuhum:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkuhus:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkuwum:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vpkuwus:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrefp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_rfi:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::RFI(ctx.PC, ctx.MSR.MSR, ctx.SRR.SRR0, ctx.SRR.SRR1);"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_vrfim:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrfin:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrfip:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrfiz:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrlb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrlh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrlimi128:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrlw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vrsqrtefp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;	//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsel:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsl:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vslb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsldoi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;		//+
	case PPC::Decoder::ASM::EInstruction::eInstruction_vslh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break; 
	case PPC::Decoder::ASM::EInstruction::eInstruction_vslo:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break; 
	case PPC::Decoder::ASM::EInstruction::eInstruction_vslw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break; 
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsplth:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltisb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltish:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltisw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vspltw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsr:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrab:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrah:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsraw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsro:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsrw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubcuw:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubfp:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubsbs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubshs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubsws:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsububm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsububs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubuhm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubuhs:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubuwm:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vsubuws:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupkd3d128:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupkhpx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupkhsb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupkhsh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupklpx:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupklsb:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vupklsh:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;
	case PPC::Decoder::ASM::EInstruction::eInstruction_vxor:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

		//extra
	case PPC::Decoder::ASM::EInstruction::eInstruction_icbi:
		codeGenNode.generalStrData = "\tPPC::StaticRecompile::ASM::ICBI(ctx.GPR.GPR, ctx.memory, " + ASMInstruction->parameterTokens[0].data + ", " +
			ASMInstruction->parameterTokens[1].data + ");"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_rotlwi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	case PPC::Decoder::ASM::EInstruction::eInstruction_rotrwi:CPP_IMPL_CODE_GEN(CPP_IMPL_NO_FUNC) break;

	//catch all
	case PPC::Decoder::ASM::EInstruction::eInstruction_MAX:
		codeGenNode.generalStrData = "\t//THIS SHOULD NEVER BE SEEN, A INSTRUCTION IS SOME HOW OUTSIDE THE NORMAL ENUM VALUE!!! INVESTIGATE"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	default:
		codeGenNode.generalStrData = "\t//THIS SHOULD NEVER BE SEEN, A INSTRUCTION IS SOME HOW OUTSIDE THE NORMAL ENUM VALUE!!! INVESTIGATE"; //instruction to C++
		codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; //comment of old ASM
		codeGenNode.generalStrData += "\n"; //adds extra space
		codeGenTree->emplace_back(codeGenNode);
		break;

	}
}

//processes a function into a series of nodes
static inline void CodeGen_ProcessFunctionASTNode(PPC::Backend::CppCodeGen::CppTranslationUnits* codeGenTrees,
	const PPC::AST::SecondPass::ASTSecondPass_Node* secondPassASTTree, uint32& ASTTreeIndex, const size_t& ASTTreeLength)
{
	//generate the prototype
	PPC::Backend::CppCodeGen::CodeGenNode node;
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::FunctionPrototype;
	node.functionMetadata.funcName = secondPassASTTree[ASTTreeIndex].functionMetaData.funcName;
	codeGenTrees->header.emplace_back(node);

	//generates the implementation
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::FunctionImpl;
	node.functionMetadata.funcName = secondPassASTTree[ASTTreeIndex].functionMetaData.funcName;
	codeGenTrees->source.emplace_back(node);

	//adds {
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Operator_Curly_Bracket_Open;
	node.generalStrData = "{";
	codeGenTrees->source.emplace_back(node);

	//adds a "GameCube::GameCubeRegisters ctx;" context for registers
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::GenaricCodeLine;
	node.generalStrData = "\tGameCube::GameCubeRegisters ctx;\n";
	codeGenTrees->source.emplace_back(node);

	//processes ASM Instructions
	size_t instructionCount = secondPassASTTree[ASTTreeIndex].functionMetaData.instructions.size();
	for (uint32 i = 0; i < instructionCount; ++i)
		CodeGen_ProcessASMInstructionASTNode(&codeGenTrees->source, i,
			&secondPassASTTree[ASTTreeIndex].functionMetaData.instructions[i],
			(i + 1 < instructionCount ? &secondPassASTTree[ASTTreeIndex].functionMetaData.instructions[i + 1] : nullptr));

	//process jump labels
	for (uint32 i = 0; i < secondPassASTTree[ASTTreeIndex].functionMetaData.jumpLabels.size(); ++i)
	{
		//adds label
		const PPC::AST::SecondPass::ASTSecondPass_Node_JumpLabel jumpLabel = secondPassASTTree[ASTTreeIndex].functionMetaData.jumpLabels[i];
		node.generalStrData = jumpLabel.labelName;
		node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::JumpLabel;
		codeGenTrees->source.emplace_back(node);

		//process the label's instructions
		instructionCount = jumpLabel.instructions.size();
		for (uint32 t = 0; t < instructionCount; ++t)
			CodeGen_ProcessASMInstructionASTNode(&codeGenTrees->source, i,
				&jumpLabel.instructions[t],
				(t + 1 < instructionCount ? &jumpLabel.instructions[t + 1] : nullptr));
	}

	//adds }
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Operator_Curly_Bracket_Closed;
	node.generalStrData = "}";
	codeGenTrees->source.emplace_back(node);
}

//processes a object into a series of nodes
static inline void CodeGen_ProcessObjectASTNode(PPC::Backend::CppCodeGen::CppTranslationUnits* codeGenTrees,
	const PPC::AST::SecondPass::ASTSecondPass_Node* secondPassASTTree, uint32& ASTTreeIndex, const size_t& ASTTreeLength)
{
	PPC::AST::SecondPass::ASTSecondPass_Node secondASTNode = secondPassASTTree[ASTTreeIndex];

	//generate the prototype
	PPC::Backend::CppCodeGen::CodeGenNode node;
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::ObjectPrototype;
	node.objectMetadata.objName = secondASTNode.objMetaData.objName;
	codeGenTrees->header.emplace_back(node);

	//adds {
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Operator_Curly_Bracket_Open;
	node.generalStrData = "{";
	codeGenTrees->header.emplace_back(node);

	//processes variables
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::Keyword_ControlFlow;
	for (uint32 i = 0; i < secondASTNode.objMetaData.variables.size(); ++i)
	{
		//process the datatype
		switch (secondASTNode.objMetaData.variables[i].tokens[0].datatypeMetadata.datatype)
		{
		case PPC::Util::Datatype::Skip_Uint16:
			node.generalStrData = "uint16_t";
			break;
		case PPC::Util::Datatype::Byte:
			node.generalStrData = "uint8_t";
			break;
		case PPC::Util::Datatype::Byte_4:

			//if it's a hex value
			if (secondASTNode.objMetaData.variables[i].tokens[1].type == PPC::Token::TokenType::Literal_HexValue)
				node.generalStrData = "uint32_t";
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
		codeGenTrees->header.emplace_back(node);
	}

	//adds }
	node.type = PPC::Backend::CppCodeGen::CodeGenNodeType::ObjectEnd;
	node.generalStrData = "}";
	codeGenTrees->header.emplace_back(node);
}

//generates C++ code bits from fine-grain AST
PPC::Backend::CppCodeGen::CppTranslationUnits PPC::Backend::CppCodeGen::RunCodeGen(const std::vector<PPC::AST::SecondPass::ASTSecondPass_Node>& secondPassASTTree,
	const std::string& filename)
{
	PPC::Backend::CppCodeGen::CppTranslationUnits codeGenTrees;

	const size_t ASTTreeLength = secondPassASTTree.size();
	codeGenTrees.header.reserve(ASTTreeLength + 1);
	codeGenTrees.source.reserve(ASTTreeLength + 1);

	//adds includes at the top of the header file
	PPC::Backend::CppCodeGen::CodeGenNode includeGen;
	includeGen.generalStrData = "#ifndef CppCodeGenDump_" + filename + "_HPP\n#define CppCodeGenDump_" + filename + "_HPP\n"; //include gaurd start
	codeGenTrees.header.emplace_back(includeGen);

	//adds includes at the top of the source file
	includeGen.generalStrData = "#include \"includes/PPC/StaticRecompile/Macros.h\"\n#include \"includes/GameCubeRegisters.h\""; //static recomp includes
	includeGen.generalStrData += "\n#include \"CppCodeGenDump_" + filename + ".hpp\""; //header file of this file
	includeGen.generalStrData += "\n#include <iostream>\n\n"; //standard lib Cout	
	codeGenTrees.source.emplace_back(includeGen);

	//goes through the AST tree
	for (uint32 i = 0; i < ASTTreeLength; ++i)
	{
		//processes a function
		if (secondPassASTTree[i].type == PPC::AST::SecondPass::ASTSecondPass_NodeType::Function)
			CodeGen_ProcessFunctionASTNode(&codeGenTrees, secondPassASTTree.data(), i, ASTTreeLength);

		//processes a object
		else if (secondPassASTTree[i].type == PPC::AST::SecondPass::ASTSecondPass_NodeType::Object)
			CodeGen_ProcessObjectASTNode(&codeGenTrees, secondPassASTTree.data(), i, ASTTreeLength);
	}

	includeGen.generalStrData = "\n\n#endif"; //include gaurd end
	codeGenTrees.header.emplace_back(includeGen);

	return codeGenTrees;
}
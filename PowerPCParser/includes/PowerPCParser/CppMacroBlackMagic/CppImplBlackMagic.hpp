#pragma once

//defines various macros for auto writing the string version of C++ functions when outputting code

#include <PowerPCParser/FineGrainAST/FineGrainAST.hpp>

//defines a macro for getting the GC context general purpose registers
#define CFS_GC_GENERAL_REGISTERS "ctx.GPR.GPR, "

//defines a macro for getting the GC context
#define CFS_GC_CONTEXT "ctx, "

//defines a macro for getting the GC context condition register
#define CFS_GC_CONDITION_REGISTER "ctx.CR.CR, "

//defines a macro for getting the GC context condition register
#define CFS_GC_CONDITION_REGISTER_END "ctx.CR.CR"

//gets a parameter parsed from the asm instruction
#define CFS_INSTRUCTION_PARAMETER(index) + ASMInstruction->parameterTokens[(index)].data + ", "

//gets a parameter parsed from the asm instruction
#define CFS_INSTRUCTION_PARAMETER_START(index) ASMInstruction->parameterTokens[(index)].data + ", "

//gets a parameter parsed from the asm instruction
#define CFS_INSTRUCTION_PARAMETER_END(index) + ASMInstruction->parameterTokens[(index)].data

//implemnts a string output function
#define CFS_PROTOTYPE(funcName, funcImplName, params) static inline std::string funcName (const PPC::AST::SecondPass::ASTSecondPass_Node_ASMInstruction* ASMInstruction) {return std::string(std::string("\tPPC::StaticRecompile::ASM::") + std::string(#funcImplName) + "(" + params + ");") ;}

//defines a macro for when no function is implemented for a instruction
#define CPP_IMPL_NO_FUNC "\t//THIS INSTRUCTION HAS NO C++ FUNCTION IMPL"

//defines impl code for a switch case for parsing ASM instructions
#define CPP_IMPL_CODE_GEN(cppFunc) codeGenNode.generalStrData = cppFunc ; /*C++ code*/ \
codeGenNode.generalStrData += std::string(" //") + CodeGen_ProcessASMInstructionIntoComment(ASMInstruction).generalStrData; /*comment of old ASM*/ \
codeGenNode.generalStrData += "\n"; /*adds extra space */ \
codeGenTree->emplace_back(codeGenNode);
#ifndef PPC_ARITHMETIC_H
#define PPC_ARITHMETIC_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Function prototypes for PowerPC arithmetic instructions
            CFS_PROTOTYPE(CPP_FUNC_STR_ADD, ADD, CFS_GC_GENERAL_REGISTERS CFS_INSTRUCTION_PARAMETER(0) CFS_INSTRUCTION_PARAMETER(1) CFS_INSTRUCTION_PARAMETER_END(2))
            CFS_PROTOTYPE(CPP_FUNC_STR_ADDI, ADDI, CFS_GC_CONTEXT CFS_INSTRUCTION_PARAMETER(0) CFS_INSTRUCTION_PARAMETER(1) CFS_INSTRUCTION_PARAMETER_END(2))
           CFS_PROTOTYPE(CPP_FUNC_STR_ADDIC, ADDIC, CFS_GC_GENERAL_REGISTERS CFS_INSTRUCTION_PARAMETER(0) CFS_INSTRUCTION_PARAMETER(1) CFS_INSTRUCTION_PARAMETER_END(2))
          CFS_PROTOTYPE(CPP_FUNC_STR_ADDIC_DOT, ADDIC_DOT, CFS_GC_GENERAL_REGISTERS CFS_INSTRUCTION_PARAMETER(0) CFS_INSTRUCTION_PARAMETER(1) CFS_INSTRUCTION_PARAMETER(2) CFS_GC_CONDITION_REGISTER_END)
           // void ADDIS(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM);
           // void ADDME(uint32_t* registers, uint32_t rD, uint32_t rA);
           // void ADDME_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);
           // void ADDZE(uint32_t* registers, uint32_t rD, uint32_t rA);
           // void ADDZE_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);
           // void SUBF(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
           // void SUBFIC(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM);
           // void SUBFME(uint32_t* registers, uint32_t rD, uint32_t rA);
           // void SUBFME_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);
           // void SUBFZE(uint32_t* registers, uint32_t rD, uint32_t rA);
           // void SUBFZE_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);
           // void NEG(uint32_t* registers, uint32_t rD, uint32_t rA);
           // void NEG_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_ARITHMETIC_H

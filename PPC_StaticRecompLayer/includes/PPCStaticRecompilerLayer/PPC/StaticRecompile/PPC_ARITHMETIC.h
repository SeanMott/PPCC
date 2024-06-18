#ifndef PPC_ARITHMETIC_H
#define PPC_ARITHMETIC_H

#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Function prototypes for PowerPC arithmetic instructions
            void ADD(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
            void ADDI(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int16_t IMM);
            void ADDIC(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM);
            void ADDIC_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM, uint32_t* CR0);
            void ADDIS(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM);
            void ADDME(uint32_t* registers, uint32_t rD, uint32_t rA);
            void ADDME_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);
            void ADDZE(uint32_t* registers, uint32_t rD, uint32_t rA);
            void ADDZE_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);
            void SUBF(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
            void SUBFIC(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM);
            void SUBFME(uint32_t* registers, uint32_t rD, uint32_t rA);
            void SUBFME_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);
            void SUBFZE(uint32_t* registers, uint32_t rD, uint32_t rA);
            void SUBFZE_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);
            void NEG(uint32_t* registers, uint32_t rD, uint32_t rA);
            void NEG_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_ARITHMETIC_H

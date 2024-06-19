#ifndef PPC_ARITHMETIC_H
#define PPC_ARITHMETIC_H

#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Function prototypes for PowerPC arithmetic instructions
            void ADD(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, uint32_t rB);
            void ADDI(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int16_t IMM);
            void ADDIC(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int32_t SIMM);
            void ADDIC_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int32_t SIMM);
            void ADDIS(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int32_t SIMM);
            void ADDME(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void ADDME_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void ADDZE(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void ADDZE_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void SUBF(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, uint32_t rB);
            void SUBFIC(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int32_t SIMM);
            void SUBFME(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void SUBFME_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void SUBFZE(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void SUBFZE_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void NEG(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);
            void NEG_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_ARITHMETIC_H

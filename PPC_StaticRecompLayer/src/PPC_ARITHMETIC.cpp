#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_ARITHMETIC.h>
#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>
#include <iostream>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the add instruction
            void ADD(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, uint32_t rB) {
                ctx.GPR.GPR[rD] = ctx.GPR.GPR[rA] + ctx.GPR.GPR[rB];
            }

            // Emulates the addi instruction (Add Immediate)
            void ADDI(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int16_t IMM) {
                ctx.GPR.GPR[rD] = ctx.GPR.GPR[rA] + static_cast<int32_t>(IMM);

                std::cout << "ADDI: Added 0x" << std::hex << IMM << " to r" << rA
                    << " (0x" << ctx.GPR.GPR[rA] << ") -> 0x" << ctx.GPR.GPR[rD]
                    << " in r" << rD << std::endl;
            }

            // Emulates the addic instruction
            void ADDIC(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int32_t SIMM) {
                uint64_t result = (uint64_t)ctx.GPR.GPR[rA] + SIMM;
                ctx.GPR.GPR[rD] = (uint32_t)result;
            }

            // Emulates the addic. instruction (sets condition register CR0)
            void ADDIC_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int32_t SIMM) {
                uint64_t result = (uint64_t)ctx.GPR.GPR[rA] + SIMM;
                ctx.GPR.GPR[rD] = (uint32_t)result;
                ctx.CR.CR = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the addis instruction
            void ADDIS(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int32_t SIMM) {
                ctx.GPR.GPR[rD] = ctx.GPR.GPR[rA] + (SIMM << 16);
            }

            // Emulates the addme instruction
            void ADDME(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = (uint64_t)ctx.GPR.GPR[rA] + 0xFFFFFFFF;
                ctx.GPR.GPR[rD] = (uint32_t)result + 1; // Increment result
            }

            // Emulates the addme. instruction (sets condition register CR0)
            void ADDME_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = (uint64_t)ctx.GPR.GPR[rA] + 0xFFFFFFFF;
                ctx.GPR.GPR[rD] = (uint32_t)result + 1; // Increment result
                ctx.CR.CR = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the addze instruction
            void ADDZE(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = (uint64_t)ctx.GPR.GPR[rA];
                ctx.GPR.GPR[rD] = (uint32_t)result + 1; // Increment result
            }

            // Emulates the addze. instruction (sets condition register CR0)
            void ADDZE_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = (uint64_t)ctx.GPR.GPR[rA];
                ctx.GPR.GPR[rD] = (uint32_t)result + 1; // Increment result
                ctx.CR.CR = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the subf instruction
            void SUBF(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, uint32_t rB) {
                ctx.GPR.GPR[rD] = ctx.GPR.GPR[rB] - ctx.GPR.GPR[rA];
            }

            // Emulates the subfic instruction
            void SUBFIC(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int32_t SIMM) {
                ctx.GPR.GPR[rD] = SIMM - ctx.GPR.GPR[rA];
            }

            // Emulates the subfme instruction
            void SUBFME(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = ~ctx.GPR.GPR[rA] + 1;
                ctx.GPR.GPR[rD] = (uint32_t)result - 1;
            }

            // Emulates the subfme. instruction (sets condition register CR0)
            void SUBFME_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = ~ctx.GPR.GPR[rA] + 1;
                ctx.GPR.GPR[rD] = (uint32_t)result - 1;
                ctx.CR.CR = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the subfze instruction
            void SUBFZE(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = ~ctx.GPR.GPR[rA] + 1;
                ctx.GPR.GPR[rD] = (uint32_t)result;
            }

            // Emulates the subfze. instruction (sets condition register CR0)
            void SUBFZE_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = ~ctx.GPR.GPR[rA] + 1;
                ctx.GPR.GPR[rD] = (uint32_t)result;
                ctx.CR.CR = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the neg instruction
            void NEG(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                ctx.GPR.GPR[rD] = ~ctx.GPR.GPR[rA] + 1;
            }

            // Emulates the neg. instruction (sets condition register CR0)
            void NEG_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA) {
                uint64_t result = ~ctx.GPR.GPR[rA] + 1;
                ctx.GPR.GPR[rD] = (uint32_t)result;
                ctx.CR.CR = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

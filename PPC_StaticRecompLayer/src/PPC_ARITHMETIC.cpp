#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_ARITHMETIC.h>
#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>
#include <iostream>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the add instruction
            void ADD(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = registers[rA] + registers[rB];
            }

            // Emulates the addi instruction (Add Immediate)
            void ADDI(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, int16_t IMM) {
                ctx.GPR.GPR[rD] = ctx.GPR.GPR[rA] + static_cast<int32_t>(IMM);

                std::cout << "ADDI: Added 0x" << std::hex << IMM << " to r" << rA
                    << " (0x" << ctx.GPR.GPR[rA] << ") -> 0x" << ctx.GPR.GPR[rD]
                    << " in r" << rD << std::endl;
            }

            // Emulates the addic instruction
            void ADDIC(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM) {
                uint64_t result = (uint64_t)registers[rA] + SIMM;
                registers[rD] = (uint32_t)result;
            }

            // Emulates the addic. instruction (sets condition register CR0)
            void ADDIC_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM, uint32_t* CR0) {
                uint64_t result = (uint64_t)registers[rA] + SIMM;
                registers[rD] = (uint32_t)result;
                *CR0 = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the addis instruction
            void ADDIS(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM) {
                registers[rD] = registers[rA] + (SIMM << 16);
            }

            // Emulates the addme instruction
            void ADDME(uint32_t* registers, uint32_t rD, uint32_t rA) {
                uint64_t result = (uint64_t)registers[rA] + 0xFFFFFFFF;
                registers[rD] = (uint32_t)result + 1; // Increment result
            }

            // Emulates the addme. instruction (sets condition register CR0)
            void ADDME_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0) {
                uint64_t result = (uint64_t)registers[rA] + 0xFFFFFFFF;
                registers[rD] = (uint32_t)result + 1; // Increment result
                *CR0 = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the addze instruction
            void ADDZE(uint32_t* registers, uint32_t rD, uint32_t rA) {
                uint64_t result = (uint64_t)registers[rA];
                registers[rD] = (uint32_t)result + 1; // Increment result
            }

            // Emulates the addze. instruction (sets condition register CR0)
            void ADDZE_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0) {
                uint64_t result = (uint64_t)registers[rA];
                registers[rD] = (uint32_t)result + 1; // Increment result
                *CR0 = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the subf instruction
            void SUBF(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = registers[rB] - registers[rA];
            }

            // Emulates the subfic instruction
            void SUBFIC(uint32_t* registers, uint32_t rD, uint32_t rA, int32_t SIMM) {
                registers[rD] = SIMM - registers[rA];
            }

            // Emulates the subfme instruction
            void SUBFME(uint32_t* registers, uint32_t rD, uint32_t rA) {
                uint64_t result = ~registers[rA] + 1;
                registers[rD] = (uint32_t)result - 1;
            }

            // Emulates the subfme. instruction (sets condition register CR0)
            void SUBFME_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0) {
                uint64_t result = ~registers[rA] + 1;
                registers[rD] = (uint32_t)result - 1;
                *CR0 = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the subfze instruction
            void SUBFZE(uint32_t* registers, uint32_t rD, uint32_t rA) {
                uint64_t result = ~registers[rA] + 1;
                registers[rD] = (uint32_t)result;
            }

            // Emulates the subfze. instruction (sets condition register CR0)
            void SUBFZE_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0) {
                uint64_t result = ~registers[rA] + 1;
                registers[rD] = (uint32_t)result;
                *CR0 = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

            // Emulates the neg instruction
            void NEG(uint32_t* registers, uint32_t rD, uint32_t rA) {
                registers[rD] = ~registers[rA] + 1;
            }

            // Emulates the neg. instruction (sets condition register CR0)
            void NEG_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t* CR0) {
                uint64_t result = ~registers[rA] + 1;
                registers[rD] = (uint32_t)result;
                *CR0 = (result >> 32) ? 1 : 0; // Set carry bit in CR0
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_COMPARASON.h>
#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>
#include <iostream>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Helper function to update condition register field
            inline void updateCR(uint32_t* CR, uint32_t BF, bool LT, bool GT, bool EQ) {
                uint32_t mask = ~(0b111 << (BF * 4));
                *CR = (*CR & mask) | ((LT << 3 | GT << 2 | EQ << 1) << (BF * 4));
            }

            // Emulates the cmp instruction
            void CMP(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB) {
                int32_t a = static_cast<int32_t>(registers[rA]);
                int32_t b = static_cast<int32_t>(registers[rB]);
                updateCR(CR, BF, a < b, a > b, a == b);
            }

            // Emulates the cmpi instruction
            void CMPI(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, int32_t SIMM) {
                int32_t a = static_cast<int32_t>(registers[rA]);
                updateCR(CR, BF, a < SIMM, a > SIMM, a == SIMM);
            }

            // Emulates the cmpl instruction
            void CMPL(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB) {
                uint32_t a = registers[rA];
                uint32_t b = registers[rB];
                updateCR(CR, BF, a < b, a > b, a == b);
            }

            // Emulates the cmpli instruction
            void CMPLI(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t UIMM) {
                uint32_t a = registers[rA];
                updateCR(CR, BF, a < UIMM, a > UIMM, a == UIMM);
            }

            // Emulates the cmpw instruction
            void CMPW(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB) {
                int32_t a = static_cast<int32_t>(registers[rA]);
                int32_t b = static_cast<int32_t>(registers[rB]);
                updateCR(CR, BF, a < b, a > b, a == b);
            }

            // Emulates the cmpwi instruction (Compare Word Immediate)
            void CMPWI(GameCube::GameCubeRegisters& ctx, uint32_t rA, int16_t IMM) {
                int32_t regValue = static_cast<int32_t>(ctx.GPR.GPR[rA]); // Sign-extend if necessary
                int32_t immValue = static_cast<int32_t>(IMM);

                // Set CR0 based on comparison
                if (regValue < immValue) {
                    ctx.CR.CR = 0x8; // LT bit
                }
                else if (regValue > immValue) {
                    ctx.CR.CR = 0x4; // GT bit
                }
                else {
                    ctx.CR.CR = 0x2; // EQ bit
                }

                std::cout << "CMPWI: Compared r" << rA << " (0x" << std::hex << regValue
                    << ") with 0x" << std::hex << immValue << std::endl;
                std::cout << "Condition Register updated to 0x" << std::hex << ctx.CR.CR << std::endl;
            }

            // Emulates the cmplw instruction
            void CMPLW(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB) {
                uint32_t a = registers[rA];
                uint32_t b = registers[rB];
                updateCR(CR, BF, a < b, a > b, a == b);
            }

            // Emulates the cmplwi instruction
            void CMPLWI(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t UIMM) {
                uint32_t a = registers[rA];
                updateCR(CR, BF, a < UIMM, a > UIMM, a == UIMM);
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

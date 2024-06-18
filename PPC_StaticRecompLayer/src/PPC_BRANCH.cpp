#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_BRANCH.h>
#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>
#include <iostream>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the b instruction
            void B(uint32_t* PC, int32_t offset) {
                *PC += offset;
            }

            // Emulates the ba instruction
            void BA(uint32_t* PC, uint32_t address) {
                *PC = address;
            }

            // Emulates the bl instruction
            void BL(uint32_t* PC, uint32_t* LR, int32_t offset) {
                *LR = *PC + 4; // Save return address (next instruction)
                *PC += offset;
            }

            // Emulates the bla instruction
            void BLA(uint32_t* PC, uint32_t* LR, uint32_t address) {
                *LR = *PC + 4; // Save return address (next instruction)
                *PC = address;
            }

            // Emulates the bc instruction
            void BC(uint32_t* PC, uint32_t* CR, int condition, uint32_t BI, int32_t offset) {
                bool conditionMet = (*CR & (1 << (31 - BI))) != 0;
                if (condition) {
                    conditionMet = !conditionMet;
                }
                if (conditionMet) {
                    *PC += offset;
                }
            }

            // Emulates the bca instruction
            void BCA(uint32_t* PC, uint32_t* CR, int condition, uint32_t BI, uint32_t address) {
                bool conditionMet = (*CR & (1 << (31 - BI))) != 0;
                if (condition) {
                    conditionMet = !conditionMet;
                }
                if (conditionMet) {
                    *PC = address;
                }
            }

            // Emulates the bcl instruction
            void BCL(uint32_t* PC, uint32_t* LR, uint32_t* CR, int condition, uint32_t BI, int32_t offset) {
                *LR = *PC + 4; // Save return address (next instruction)
                BC(PC, CR, condition, BI, offset);
            }

            // Emulates the bcla instruction
            void BCLA(uint32_t* PC, uint32_t* LR, uint32_t* CR, int condition, uint32_t BI, uint32_t address) {
                *LR = *PC + 4; // Save return address (next instruction)
                BCA(PC, CR, condition, BI, address);
            }

            // Emulates the bcctr instruction
            void BCCTR(uint32_t* PC, uint32_t* CR, uint32_t* CTR, int condition, uint32_t BI) {
                bool conditionMet = (*CR & (1 << (31 - BI))) != 0;
                if (condition) {
                    conditionMet = !conditionMet;
                }
                if (conditionMet) {
                    *PC = *CTR;
                }
            }

            // Emulates the bcctrl instruction
            void BCCTRL(uint32_t* PC, uint32_t* LR, uint32_t* CR, uint32_t* CTR, int condition, uint32_t BI) {
                *LR = *PC + 4; // Save return address (next instruction)
                BCCTR(PC, CR, CTR, condition, BI);
            }

            // Emulates the bclr instruction
            void BCLR(uint32_t* PC, uint32_t* CR, uint32_t* LR, int condition, uint32_t BI) {
                bool conditionMet = (*CR & (1 << (31 - BI))) != 0;
                if (condition) {
                    conditionMet = !conditionMet;
                }
                if (conditionMet) {
                    *PC = *LR;
                }
            }

            // Emulates the bclrl instruction
            void BCLRL(uint32_t* PC, uint32_t* LR, uint32_t* CR, int condition, uint32_t BI) {
                *LR = *PC + 4; // Save return address (next instruction)
                BCLR(PC, CR, LR, condition, BI);
            }

            // Emulates the blr instruction
            void BLR(uint32_t* PC, uint32_t* LR) {
                *PC = *LR;
            }

            // Emulates the blrl instruction
            void BLRL(uint32_t* PC, uint32_t* LR) {
                *LR = *PC + 4; // Save return address (next instruction)
                *PC = *LR;
            }

            // Emulates the bne instruction (Branch if Not Equal)
            bool BNE_If(GameCube::GameCubeRegisters& ctx) {
                // Check the EQ bit in the Condition Register
                // Assume CR0 is used here; you might need to adjust this depending on actual usage
                bool notEqual = (ctx.CR.CR & 0x2) == 0;

                std::cout << "BNE: Condition Register = 0x" << std::hex << ctx.CR.CR << std::endl;
                std::cout << "BNE: Not Equal condition is " << std::boolalpha << notEqual << std::endl;

                return notEqual;
            }

            // Emulates the bl instruction (Branch and Link)
            void BL_If(GameCube::GameCubeRegisters& ctx, void (*target)()) {
                // Save the return address in the Link Register (LR)
                ctx.SPR.LR = ctx.PC + 4; // Save the next instruction address
                std::cout << "BL: Saving return address 0x" << std::hex << ctx.SPR.LR << " to LR" << std::endl;

                // Call the target function
                target();

                std::cout << "BL: Returning from function" << std::endl;
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

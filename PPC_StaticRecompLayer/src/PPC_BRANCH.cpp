#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_BRANCH.h>
#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>
#include <iostream>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the b instruction
            void B(GameCube::GameCubeRegisters& ctx, int32_t offset) {
                ctx.PC += offset;
            }

            // Emulates the ba instruction
            void BA(GameCube::GameCubeRegisters& ctx, uint32_t address) {
                ctx.PC = address;
            }

            // Emulates the bl instruction
            void BL(GameCube::GameCubeRegisters& ctx, int32_t offset) {
                ctx.SPR.LR = ctx.PC + 4; // Save return address (next instruction)
                ctx.PC += offset;
            }

            // Emulates the bla instruction
            void BLA(GameCube::GameCubeRegisters& ctx, uint32_t address) {
                ctx.SPR.LR = ctx.PC + 4; // Save return address (next instruction)
                ctx.PC = address;
            }

            // Emulates the bc instruction
            void BC(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI, int32_t offset) {
                bool conditionMet = (ctx.CR.CR & (1 << (31 - BI))) != 0;
                if (condition) {
                    conditionMet = !conditionMet;
                }
                if (conditionMet) {
                    ctx.PC += offset;
                }
            }

            // Emulates the bca instruction
            void BCA(GameCube::GameCubeRegisters& ctx,  int condition, uint32_t BI, uint32_t address) {
                bool conditionMet = (ctx.CR.CR & (1 << (31 - BI))) != 0;
                if (condition) {
                    conditionMet = !conditionMet;
                }
                if (conditionMet) {
                    ctx.PC = address;
                }
            }

            // Emulates the bcl instruction
            void BCL(GameCube::GameCubeRegisters& ctx,  int condition, uint32_t BI, int32_t offset) {
                ctx.SPR.LR = ctx.PC + 4; // Save return address (next instruction)
                BC(ctx, condition, BI, offset);
            }

            // Emulates the bcla instruction
            void BCLA(GameCube::GameCubeRegisters& ctx,  int condition, uint32_t BI, uint32_t address) {
                ctx.SPR.LR = ctx.PC + 4; // Save return address (next instruction)
                BCA(ctx, condition, BI, address);
            }

            // Emulates the bcctr instruction
            void BCCTR(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI) {
                bool conditionMet = (ctx.CR.CR & (1 << (31 - BI))) != 0;
                if (condition) {
                    conditionMet = !conditionMet;
                }
                if (conditionMet) {
                    ctx.PC = ctx.SPR.CTR;
                }
            }

            // Emulates the bcctrl instruction
            void BCCTRL(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI) {
                ctx.SPR.LR = ctx.PC + 4; // Save return address (next instruction)
                BCCTR(ctx, condition, BI);
            }

            // Emulates the bclr instruction
            void BCLR(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI) {
                bool conditionMet = (ctx.CR.CR & (1 << (31 - BI))) != 0;
                if (condition) {
                    conditionMet = !conditionMet;
                }
                if (conditionMet) {
                    ctx.PC = ctx.SPR.LR;
                }
            }

            // Emulates the bclrl instruction
            void BCLRL(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI) {
                ctx.SPR.LR = ctx.PC + 4; // Save return address (next instruction)
                BCLR(ctx, condition, BI);
            }

            // Emulates the blr instruction
            void BLR(GameCube::GameCubeRegisters& ctx) {
                ctx.PC = ctx.SPR.LR;
            }

            // Emulates the blrl instruction
            void BLRL(GameCube::GameCubeRegisters& ctx) {
                ctx.SPR.LR = ctx.PC + 4; // Save return address (next instruction)
                ctx.PC = ctx.SPR.LR;
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

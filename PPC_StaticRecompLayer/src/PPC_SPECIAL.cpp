#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_SPECIAL.h>
#include <iostream>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the mfcr instruction
            void MFCR(uint32_t* registers, uint32_t* CR, uint32_t rD) {
                registers[rD] = *CR;
            }

            // Emulates the mfspr instruction
            void MFSPR(uint32_t* registers, uint64_t* SPR, uint32_t rD, uint32_t spr) {
                registers[rD] = static_cast<uint32_t>(SPR[spr]);
            }

            // Emulates the mtspr instruction
            void MTSPR(uint64_t* SPR, uint32_t* registers, uint32_t spr, uint32_t rS) {
                SPR[spr] = registers[rS];
            }

            // Emulates the mfsr instruction
            void MFSR(uint32_t* registers, uint32_t* SR, uint32_t rD, uint32_t sr) {
                registers[rD] = SR[sr];
            }

            // Emulates the mtsr instruction
            void MTSR(uint32_t* SR, uint32_t* registers, uint32_t sr, uint32_t rS) {
                SR[sr] = registers[rS];
            }

            // Emulates the mfsrin instruction
            void MFSRIN(uint32_t* registers, uint32_t* SR, uint32_t rD, uint32_t rB) {
                uint32_t effectiveAddress = registers[rB] >> 28;
                registers[rD] = SR[effectiveAddress];
            }

            // Emulates the mtsrin instruction
            void MTSRIN(uint32_t* SR, uint32_t* registers, uint32_t rS, uint32_t rB) {
                uint32_t effectiveAddress = registers[rB] >> 28;
                SR[effectiveAddress] = registers[rS];
            }

            // Emulates the mftb instruction
            void MFTB(uint32_t* registers, uint64_t* TBR, uint32_t rD, uint32_t tbr) {
                registers[rD] = static_cast<uint32_t>(TBR[tbr]);
            }

            // Emulates the mtlr instruction (Move to Link Register)
            void MTLR(GameCube::GameCubeRegisters& ctx, uint32_t rS) {
                ctx.SPR.LR = ctx.GPR.GPR[rS];

                std::cout << "MTLR: Moved r" << rS << " (0x" << std::hex << ctx.GPR.GPR[rS]
                    << ") to Link Register (LR)" << std::endl;
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

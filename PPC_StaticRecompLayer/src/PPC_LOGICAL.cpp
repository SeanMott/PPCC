#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_LOGICAL.h>
#include <iostream>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the and instruction
            void AND(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = registers[rA] & registers[rB];
            }

            // Emulates the andi. instruction (AND Immediate and Record)
            void ANDI_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, uint16_t IMM) {
                // Perform bitwise AND between the contents of rA and the immediate value
                ctx.GPR.GPR[rD] = ctx.GPR.GPR[rA] & IMM;

                // Update Condition Register (CR)
                // Assuming CR0 field; CR has different fields that can be set by different operations
                ctx.CR.CR = (ctx.GPR.GPR[rD] == 0) ? 0x2 : 0x0; // Set Z bit if result is zero

                // Print debugging information
                std::cout << "ANDI.: r" << rD << " = r" << rA << " & 0x" << std::hex << IMM
                    << " -> 0x" << ctx.GPR.GPR[rD] << std::endl;
                std::cout << "Condition Register updated to 0x" << std::hex << ctx.CR.CR << std::endl;
            }

            // Emulates the andc instruction
            void ANDC(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = registers[rA] & ~registers[rB];
            }

            // Emulates the andis. instruction
            void ANDIS_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM, uint32_t* CR0) {
                registers[rD] = registers[rA] & (UIMM << 16);
                *CR0 = (registers[rD] == 0) ? 1 : 0; // Set CR0 based on result
            }

            // Emulates the or instruction
            void OR(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = registers[rA] | registers[rB];
            }

            // Emulates the ori instruction
            void ORI(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM) {
                registers[rD] = registers[rA] | UIMM;
            }

            // Emulates the orc instruction
            void ORC(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = registers[rA] | ~registers[rB];
            }

            // Emulates the oris instruction
            void ORIS(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM) {
                registers[rD] = registers[rA] | (UIMM << 16);
            }

            // Emulates the xor instruction
            void XOR(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = registers[rA] ^ registers[rB];
            }

            // Emulates the xori instruction
            void XORI(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM) {
                registers[rD] = registers[rA] ^ UIMM;
            }

            // Emulates the xoris instruction
            void XORIS(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM) {
                registers[rD] = registers[rA] ^ (UIMM << 16);
            }

            // Emulates the nand instruction
            void NAND(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = ~(registers[rA] & registers[rB]);
            }

            // Emulates the nor instruction
            void NOR(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = ~(registers[rA] | registers[rB]);
            }

            // Emulates the eqv instruction
            void EQV(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                registers[rD] = ~(registers[rA] ^ registers[rB]);
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

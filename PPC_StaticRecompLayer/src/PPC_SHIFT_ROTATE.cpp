#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_SHIFT_ROTATE.h>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the slw instruction
            void SLW(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t shiftAmount = registers[rB] & 0x1F; // Only use the lower 5 bits for shift amount
                registers[rD] = registers[rA] << shiftAmount;
            }

            // Emulates the srw instruction
            void SRW(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t shiftAmount = registers[rB] & 0x1F; // Only use the lower 5 bits for shift amount
                registers[rD] = registers[rA] >> shiftAmount;
            }

            // Emulates the sraw instruction
            void SRAW(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t shiftAmount = registers[rB] & 0x1F; // Only use the lower 5 bits for shift amount
                registers[rD] = static_cast<int32_t>(registers[rA]) >> shiftAmount;
            }

            // Emulates the srawi instruction
            void SRAWI(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t SH) {
                uint32_t shiftAmount = SH & 0x1F; // Only use the lower 5 bits for shift amount
                registers[rD] = static_cast<int32_t>(registers[rA]) >> shiftAmount;
            }

            // Emulates the rlwimi instruction
            void RLWIMI(uint32_t* registers, uint32_t rD, uint32_t rS, uint32_t SH, uint32_t MB, uint32_t ME) {
                uint32_t mask = 0xFFFFFFFF << (31 - ME) >> (31 - ME + MB) << MB;
                uint32_t rotated = (registers[rS] << SH) | (registers[rS] >> (32 - SH));
                registers[rD] = (registers[rD] & ~mask) | (rotated & mask);
            }

            // Emulates the rlwinm instruction
            void RLWINM(uint32_t* registers, uint32_t rD, uint32_t rS, uint32_t SH, uint32_t MB, uint32_t ME) {
                uint32_t rotated = (registers[rS] << SH) | (registers[rS] >> (32 - SH));
                uint32_t mask = 0xFFFFFFFF << (31 - ME) >> (31 - ME + MB) << MB;
                registers[rD] = rotated & mask;
            }

            // Emulates the rlwnm instruction
            void RLWNM(uint32_t* registers, uint32_t rD, uint32_t rS, uint32_t rB, uint32_t MB, uint32_t ME) {
                uint32_t shiftAmount = registers[rB] & 0x1F; // Only use the lower 5 bits for shift amount
                uint32_t rotated = (registers[rS] << shiftAmount) | (registers[rS] >> (32 - shiftAmount));
                uint32_t mask = 0xFFFFFFFF << (31 - ME) >> (31 - ME + MB) << MB;
                registers[rD] = rotated & mask;
            }

            // Emulates the lis instruction (Load Immediate Shifted)
            void LIS(uint32_t* registers, uint32_t rD, uint16_t IMM) {
                registers[rD] = IMM << 16;
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

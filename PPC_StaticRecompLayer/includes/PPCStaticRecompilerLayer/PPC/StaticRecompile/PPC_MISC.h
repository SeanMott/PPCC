#ifndef PPC_MISC_H
#define PPC_MISC_H

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for additional instructions
            void NOP();
            void TW(uint32_t* registers, uint32_t TO, uint32_t rA, uint32_t rB);
            void TWI(uint32_t* registers, uint32_t TO, uint32_t rA, int16_t SIMM);
            void TD(uint32_t* registers, uint32_t TO, uint32_t rA, uint32_t rB);
            void TDI(uint32_t* registers, uint32_t TO, uint32_t rA, int16_t SIMM);
            void RFCI(uint32_t* PC, uint64_t* MSR, uint64_t* SRR0, uint64_t* SRR1);
            void RFI(uint32_t* PC, uint64_t* MSR, uint64_t* SRR0, uint64_t* SRR1);
            void RFID(uint32_t* PC, uint64_t* MSR, uint64_t* SRR0, uint64_t* SRR1);
            void DCBA(uint32_t* registers, uint32_t rA, uint32_t rB);
            void DCBF(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void DCBI(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void DCBST(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void DCBT(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void DCBTST(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void DCBZ(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void ICBI(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void ICBT(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void ICBTLS(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);
            void DCBTLS(uint32_t* registers, uint8_t* cache, uint32_t rA, uint32_t rB);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_MISC_H

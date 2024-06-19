#ifndef PPC_SHIFT_ROTATE_H
#define PPC_SHIFT_ROTATE_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for shift and rotate instructions
          //  void SLW(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
          //  void SRW(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
          //  void SRAW(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
          //  void SRAWI(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t SH);
          //  void RLWIMI(uint32_t* registers, uint32_t rD, uint32_t rS, uint32_t SH, uint32_t MB, uint32_t ME);
          //  void RLWINM(uint32_t* registers, uint32_t rD, uint32_t rS, uint32_t SH, uint32_t MB, uint32_t ME);
          //  void RLWNM(uint32_t* registers, uint32_t rD, uint32_t rS, uint32_t rB, uint32_t MB, uint32_t ME);
          //  void LIS(uint32_t* registers, uint32_t rD, uint16_t IMM);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_SHIFT_ROTATE_H

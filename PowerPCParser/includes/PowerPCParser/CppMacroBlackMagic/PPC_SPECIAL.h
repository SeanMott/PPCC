#ifndef PPC_SPECIAL_H
#define PPC_SPECIAL_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for system register instructions
          //  void MFCR(uint32_t* registers, uint32_t* CR, uint32_t rD);
          //  void MFSPR(uint32_t* registers, uint64_t* SPR, uint32_t rD, uint32_t spr);
          //  void MTSPR(uint64_t* SPR, uint32_t* registers, uint32_t spr, uint32_t rS);
          //  void MFSR(uint32_t* registers, uint32_t* SR, uint32_t rD, uint32_t sr);
          //  void MTSR(uint32_t* SR, uint32_t* registers, uint32_t sr, uint32_t rS);
          //  void MFSRIN(uint32_t* registers, uint32_t* SR, uint32_t rD, uint32_t rB);
          //  void MTSRIN(uint32_t* SR, uint32_t* registers, uint32_t rS, uint32_t rB);
          //  void MFTB(uint32_t* registers, uint64_t* TBR, uint32_t rD, uint32_t tbr);
          //  void MTLR(GameCube::GameCubeRegisters& ctx, uint32_t rS);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_SPECIAL_H

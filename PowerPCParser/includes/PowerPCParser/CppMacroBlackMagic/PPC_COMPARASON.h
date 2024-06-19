#ifndef PPC_COMPARASON_H
#define PPC_COMPARASON_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for compare instructions
           //void CMP(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB);
           //void CMPI(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, int32_t SIMM);
           //void CMPL(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB);
           //void CMPLI(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t UIMM);
           //void CMPW(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB);
           //void CMPWI(GameCube::GameCubeRegisters& ctx, uint32_t rA, int16_t IMM);
           //void CMPLW(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB);
           //void CMPLWI(uint32_t* registers, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t UIMM);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_COMPARASON_H

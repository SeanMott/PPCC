#ifndef PPC_LOAD_STORE_H
#define PPC_LOAD_STORE_H

#include <cstdint> // for standard integer types
#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for load instructions
            void LBZ(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset);
            void LBZU(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset);
            void LBZX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LBZUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LHZ(GameCube::GameCubeRegisters& ctx, uint32_t rD, int16_t offset, uint32_t rA);
            void LHZU(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset);
            void LHZUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LHZX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LHA(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset);
            void LHAU(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset);
            void LHAX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LHAUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LWZ(GameCube::GameCubeRegisters& ctx, uint32_t rD, int16_t offset, uint32_t rA);
            void LWZU(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset);
            void LWZX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LWZUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void STB(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, int32_t offset);
            void STBU(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, int32_t offset);
            void STBX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB);
            void STBUX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB);
            void STH(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, int32_t offset);
            void STHU(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, int32_t offset);
            void STHX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB);
            void STHUX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB);
            void STW(uint32_t* registers, uint32_t value, int16_t offset, uint32_t rA, uint8_t* memory);
            void STWU(GameCube::GameCubeRegisters& ctx, uint32_t rS, int16_t offset, uint32_t rA);
            void STWX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB);
            void STWUX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB);
            void LWA(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset);
            void LWAX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LWAUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB);
            void LI(GameCube::GameCubeRegisters& ctx, uint32_t rD, int32_t IMM);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_LOAD_STORE_H

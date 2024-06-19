#ifndef PPC_BRANCH_H
#define PPC_BRANCH_H

#include <PPCStaticRecompilerLayer/GameCubeRegisters.h>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for branch instructions
            void B(GameCube::GameCubeRegisters& ctx, int32_t offset);
            void BA(GameCube::GameCubeRegisters& ctx, uint32_t address);
            void BL(GameCube::GameCubeRegisters& ctx, int32_t offset);
            void BLA(GameCube::GameCubeRegisters& ctx, uint32_t address);
            void BC(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI, int32_t offset);
            void BCA(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI, uint32_t address);
            void BCL(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI, int32_t offset);
            void BCLA(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI, uint32_t address);
            void BCCTR(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI);
            void BCCTRL(GameCube::GameCubeRegisters& ctx, uint32_t* CTR, int condition, uint32_t BI);
            void BCLR(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI);
            void BCLRL(GameCube::GameCubeRegisters& ctx, int condition, uint32_t BI);
            void BLR(GameCube::GameCubeRegisters& ctx);
            void BLRL(GameCube::GameCubeRegisters& ctx);
            bool BNE_If(GameCube::GameCubeRegisters& ctx);
            void BL_If(GameCube::GameCubeRegisters& ctx, void (*target)());

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_BRANCH_H

#ifndef PPC_BRANCH_H
#define PPC_BRANCH_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for branch instructions
           // void B(uint32_t* PC, int32_t offset);
           // void BA(uint32_t* PC, uint32_t address);
           // void BL(uint32_t* PC, uint32_t* LR, int32_t offset);
           // void BLA(uint32_t* PC, uint32_t* LR, uint32_t address);
           // void BC(uint32_t* PC, uint32_t* CR, int condition, uint32_t BI, int32_t offset);
           // void BCA(uint32_t* PC, uint32_t* CR, int condition, uint32_t BI, uint32_t address);
           // void BCL(uint32_t* PC, uint32_t* LR, uint32_t* CR, int condition, uint32_t BI, int32_t offset);
           // void BCLA(uint32_t* PC, uint32_t* LR, uint32_t* CR, int condition, uint32_t BI, uint32_t address);
           // void BCCTR(uint32_t* PC, uint32_t* CR, uint32_t* CTR, int condition, uint32_t BI);
           // void BCCTRL(uint32_t* PC, uint32_t* LR, uint32_t* CR, uint32_t* CTR, int condition, uint32_t BI);
           // void BCLR(uint32_t* PC, uint32_t* CR, uint32_t* LR, int condition, uint32_t BI);
           // void BCLRL(uint32_t* PC, uint32_t* LR, uint32_t* CR, int condition, uint32_t BI);
           // void BLR(uint32_t* PC, uint32_t* LR);
           // void BLRL(uint32_t* PC, uint32_t* LR);
           // bool BNE_If(GameCube::GameCubeRegisters& ctx);
           // void BL_If(GameCube::GameCubeRegisters& ctx, void (*target)());

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_BRANCH_H

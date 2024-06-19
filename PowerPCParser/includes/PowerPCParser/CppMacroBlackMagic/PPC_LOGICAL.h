#ifndef PPC_LOGICAL_H
#define PPC_LOGICAL_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for logical instructions
         //  void AND(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
         //  void ANDI_DOT(GameCube::GameCubeRegisters& ctx, uint32_t rD, uint32_t rA, uint16_t IMM);
         //  void ANDC(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
         //  void ANDIS_DOT(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM, uint32_t* CR0);
         //  void OR(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
         //  void ORI(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM);
         //  void ORC(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
         //  void ORIS(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM);
         //  void XOR(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
         //  void XORI(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM);
         //  void XORIS(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t UIMM);
         //  void NAND(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
         //  void NOR(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);
         //  void EQV(uint32_t* registers, uint32_t rD, uint32_t rA, uint32_t rB);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_LOGICAL_H

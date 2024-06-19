#ifndef PPC_FLOATING_H
#define PPC_FLOATING_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for floating-point arithmetic instructions
          // void FADD(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB);
          // void FADDS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB);
          // void FSUB(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB);
          // void FSUBS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB);
          // void FMUL(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB);
          // void FMULS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB);
          // void FDIV(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB);
          // void FDIVS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB);
          // void FSQRT(double* fRegisters, uint32_t rD, uint32_t rA);
          // void FSQRTS(float* fRegisters, uint32_t rD, uint32_t rA);
          // void FSEL(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FMADD(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FMADDS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FMSUB(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FMSUBS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FNMADD(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FNMADDS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FNMSUB(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FNMSUBS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC);
          // void FRES(float* fRegisters, uint32_t rD, uint32_t rA);
          // void FRSQRTE(float* fRegisters, uint32_t rD, uint32_t rA);
          // void FCTIW(float* fRegisters, int32_t* iRegisters, uint32_t rD, uint32_t rA);
          // void FCTIWZ(float* fRegisters, int32_t* iRegisters, uint32_t rD, uint32_t rA);
          // void FCTID(double* fRegisters, int64_t* iRegisters, uint32_t rD, uint32_t rA);
          // void FCTIDZ(double* fRegisters, int64_t* iRegisters, uint32_t rD, uint32_t rA);
          // void FCMPU(double* fRegisters, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB);
          // void FCMPO(double* fRegisters, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB);
          // void FMR(double* fRegisters, uint32_t rD, uint32_t rS);
          // void FABS(double* fRegisters, uint32_t rD, uint32_t rA);
          // void FNEG(double* fRegisters, uint32_t rD, uint32_t rA);
          // void MFFS(double* fRegisters, uint64_t* FPSCR, uint32_t rD);
          // void MFFSS(float* fRegisters, uint32_t* FPSCR, uint32_t rD);
          // void MTFSB0(uint64_t* FPSCR, uint32_t bit);
          // void MTFSB1(uint64_t* FPSCR, uint32_t bit);
          // void MTFSF(uint64_t* FPSCR, uint64_t value, uint8_t mask);
          // void MTFSFI(uint64_t* FPSCR, uint32_t field, uint8_t value);
          // void FRSP(double* fRegisters, uint32_t rD, uint32_t rA);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_FLOATING_H

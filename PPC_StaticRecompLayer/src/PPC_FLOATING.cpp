#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_FLOATING.h>
#include <cmath> // for standard math functions

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the fadd instruction
            void FADD(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB) {
                fRegisters[rD] = fRegisters[rA] + fRegisters[rB];
            }

            // Emulates the fadds instruction
            void FADDS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB) {
                fRegisters[rD] = fRegisters[rA] + fRegisters[rB];
            }

            // Emulates the fsub instruction
            void FSUB(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB) {
                fRegisters[rD] = fRegisters[rA] - fRegisters[rB];
            }

            // Emulates the fsubs instruction
            void FSUBS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB) {
                fRegisters[rD] = fRegisters[rA] - fRegisters[rB];
            }

            // Emulates the fmul instruction
            void FMUL(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB) {
                fRegisters[rD] = fRegisters[rA] * fRegisters[rB];
            }

            // Emulates the fmuls instruction
            void FMULS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB) {
                fRegisters[rD] = fRegisters[rA] * fRegisters[rB];
            }

            // Emulates the fdiv instruction
            void FDIV(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB) {
                fRegisters[rD] = fRegisters[rA] / fRegisters[rB];
            }

            // Emulates the fdivs instruction
            void FDIVS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB) {
                fRegisters[rD] = fRegisters[rA] / fRegisters[rB];
            }

            // Emulates the fsqrt instruction
            void FSQRT(double* fRegisters, uint32_t rD, uint32_t rA) {
                fRegisters[rD] = std::sqrt(fRegisters[rA]);
            }

            // Emulates the fsqrts instruction
            void FSQRTS(float* fRegisters, uint32_t rD, uint32_t rA) {
                fRegisters[rD] = std::sqrt(fRegisters[rA]);
            }

            // Emulates the fsel instruction
            void FSEL(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = (fRegisters[rA] >= 0.0) ? fRegisters[rB] : fRegisters[rC];
            }


            // Emulates the fmadd instruction
            void FMADD(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = fRegisters[rA] * fRegisters[rB] + fRegisters[rC];
            }

            // Emulates the fmadds instruction
            void FMADDS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = fRegisters[rA] * fRegisters[rB] + fRegisters[rC];
            }

            // Emulates the fmsub instruction
            void FMSUB(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = fRegisters[rA] * fRegisters[rB] - fRegisters[rC];
            }

            // Emulates the fmsubs instruction
            void FMSUBS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = fRegisters[rA] * fRegisters[rB] - fRegisters[rC];
            }

            // Emulates the fnmadd instruction
            void FNMADD(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = -(fRegisters[rA] * fRegisters[rB] + fRegisters[rC]);
            }

            // Emulates the fnmadds instruction
            void FNMADDS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = -(fRegisters[rA] * fRegisters[rB] + fRegisters[rC]);
            }

            // Emulates the fnmsub instruction
            void FNMSUB(double* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = -(fRegisters[rA] * fRegisters[rB] - fRegisters[rC]);
            }

            // Emulates the fnmsubs instruction
            void FNMSUBS(float* fRegisters, uint32_t rD, uint32_t rA, uint32_t rB, uint32_t rC) {
                fRegisters[rD] = -(fRegisters[rA] * fRegisters[rB] - fRegisters[rC]);
            }

            // Emulates the fres instruction
            void FRES(float* fRegisters, uint32_t rD, uint32_t rA) {
                fRegisters[rD] = 1.0f / fRegisters[rA];
            }

            // Emulates the frsqrte instruction
            void FRSQRTE(float* fRegisters, uint32_t rD, uint32_t rA) {
                fRegisters[rD] = 1.0f / std::sqrt(fRegisters[rA]);
            }

            // Emulates the fctiw instruction
            void FCTIW(float* fRegisters, int32_t* iRegisters, uint32_t rD, uint32_t rA) {
                iRegisters[rD] = static_cast<int32_t>(std::floor(fRegisters[rA] + 0.5f));
            }

            // Emulates the fctiwz instruction
            void FCTIWZ(float* fRegisters, int32_t* iRegisters, uint32_t rD, uint32_t rA) {
                iRegisters[rD] = static_cast<int32_t>(fRegisters[rA]);
            }

            // Emulates the fctid instruction
            void FCTID(double* fRegisters, int64_t* iRegisters, uint32_t rD, uint32_t rA) {
                iRegisters[rD] = static_cast<int64_t>(std::floor(fRegisters[rA] + 0.5));
            }

            // Emulates the fctidz instruction
            void FCTIDZ(double* fRegisters, int64_t* iRegisters, uint32_t rD, uint32_t rA) {
                iRegisters[rD] = static_cast<int64_t>(fRegisters[rA]);
            }

            // Helper function to update condition register for floating-point comparisons
            inline void updateFCR(uint32_t* CR, uint32_t BF, bool LT, bool GT, bool EQ, bool unordered = false) {
                uint32_t mask = ~(0b1111 << (BF * 4));
                *CR = (*CR & mask) | ((LT << 3 | GT << 2 | EQ << 1 | unordered) << (BF * 4));
            }

            // Emulates the fcmpu instruction
            void FCMPU(double* fRegisters, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB) {
                double a = fRegisters[rA];
                double b = fRegisters[rB];
                bool unordered = std::isnan(a) || std::isnan(b);
                bool LT = a < b;
                bool GT = a > b;
                bool EQ = a == b;
                updateFCR(CR, BF, LT, GT, EQ, unordered);
            }

            // Emulates the fcmpo instruction
            void FCMPO(double* fRegisters, uint32_t* CR, uint32_t BF, uint32_t rA, uint32_t rB) {
                double a = fRegisters[rA];
                double b = fRegisters[rB];
                bool unordered = std::isnan(a) || std::isnan(b);
                bool LT = !unordered && a < b;
                bool GT = !unordered && a > b;
                bool EQ = !unordered && a == b;
                updateFCR(CR, BF, LT, GT, EQ, unordered);
            }

            // Emulates the fmr instruction
            void FMR(double* fRegisters, uint32_t rD, uint32_t rS) {
                fRegisters[rD] = fRegisters[rS];
            }

            // Emulates the fabs instruction
            void FABS(double* fRegisters, uint32_t rD, uint32_t rA) {
                fRegisters[rD] = std::fabs(fRegisters[rA]);
            }

            // Emulates the fneg instruction
            void FNEG(double* fRegisters, uint32_t rD, uint32_t rA) {
                fRegisters[rD] = -fRegisters[rA];
            }

            // Emulates the mffs instruction
            void MFFS(double* fRegisters, uint64_t* FPSCR, uint32_t rD) {
                fRegisters[rD] = static_cast<double>(*FPSCR);
            }

            // Emulates the mffss instruction (assuming single-precision)
            void MFFSS(float* fRegisters, uint32_t* FPSCR, uint32_t rD) {
                fRegisters[rD] = static_cast<float>(*FPSCR);
            }

            // Emulates the mtfsb0 instruction
            void MTFSB0(uint64_t* FPSCR, uint32_t bit) {
                *FPSCR &= ~(1ULL << (63 - bit));
            }

            // Emulates the mtfsb1 instruction
            void MTFSB1(uint64_t* FPSCR, uint32_t bit) {
                *FPSCR |= (1ULL << (63 - bit));
            }

            // Emulates the mtfsf instruction
            void MTFSF(uint64_t* FPSCR, uint64_t value, uint8_t mask) {
                uint64_t fieldMask = 0;
                for (int i = 0; i < 8; ++i) {
                    if (mask & (1 << i)) {
                        fieldMask |= (0xF000000000000000 >> (i * 4));
                    }
                }
                *FPSCR = (*FPSCR & ~fieldMask) | (value & fieldMask);
            }

            // Emulates the mtfsfi instruction
            void MTFSFI(uint64_t* FPSCR, uint32_t field, uint8_t value) {
                uint64_t mask = 0xF000000000000000 >> (field * 4);
                *FPSCR = (*FPSCR & ~mask) | ((static_cast<uint64_t>(value) << (60 - field * 4)) & mask);
            }

            // Emulates the frsp instruction
            void FRSP(double* fRegisters, uint32_t rD, uint32_t rA) {
                fRegisters[rD] = static_cast<float>(fRegisters[rA]);
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

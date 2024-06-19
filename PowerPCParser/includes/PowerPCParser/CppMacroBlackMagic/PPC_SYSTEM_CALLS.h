#ifndef PPC_SYSTEM_CALLS_H
#define PPC_SYSTEM_CALLS_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototype for system call instruction
          //  void SC(uint32_t* registers, uint64_t* MSR, uint32_t* PC, void (*systemCallHandler)(uint32_t* registers, uint64_t* MSR));

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_SYSTEM_CALLS_H

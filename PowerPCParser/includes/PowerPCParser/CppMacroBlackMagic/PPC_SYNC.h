#ifndef PPC_SYNC_H
#define PPC_SYNC_H

#include <PowerPCParser/CppMacroBlackMagic/CppImplBlackMagic.hpp>

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for synchronization instructions
          //  void SYNC();
          //  void LWSYNC();
          //  void ISYNC();
          //  void EIEIO();

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_SYNC_H

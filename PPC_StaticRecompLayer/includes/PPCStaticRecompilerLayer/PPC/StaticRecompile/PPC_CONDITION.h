#ifndef PPC_CONDITION_H
#define PPC_CONDITION_H

#include <cstdint> // for standard integer types

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Prototypes for CR logical instructions
            void CRAND(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB);
            void CRANDC(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB);
            void CREQV(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB);
            void CRNAND(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB);
            void CRNOR(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB);
            void CROR(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB);
            void CRORC(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB);
            void CRXOR(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB);

            // Prototypes for CR manipulation instructions
            void MCRF(uint32_t* CR, uint32_t BF, uint32_t BFA);
            void MCRFS(uint32_t* CR, uint32_t* FPSCR, uint32_t BF, uint32_t BFA);
            void MTCRF(uint32_t* CR, uint32_t CRM, uint32_t value);
            void MTOCRF(uint32_t* CR, uint32_t CRM, uint32_t value);

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#endif // PPC_CONDITION_H

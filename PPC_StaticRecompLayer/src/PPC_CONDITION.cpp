#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_CONDITION.h>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Helper function to set condition register field
            inline void setCRField(uint32_t* CR, uint32_t BF, uint32_t value) {
                uint32_t mask = 0xF << ((7 - BF) * 4);
                *CR = (*CR & ~mask) | ((value & 0xF) << ((7 - BF) * 4));
            }

            // Emulates the crand instruction
            void CRAND(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB) {
                uint32_t result = ((*CR >> ((7 - BA) * 4)) & 0xF) & ((*CR >> ((7 - BB) * 4)) & 0xF);
                setCRField(CR, BF, result);
            }

            // Emulates the crandc instruction
            void CRANDC(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB) {
                uint32_t result = ((*CR >> ((7 - BA) * 4)) & 0xF) & ~((*CR >> ((7 - BB) * 4)) & 0xF);
                setCRField(CR, BF, result);
            }

            // Emulates the creqv instruction
            void CREQV(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB) {
                uint32_t result = ~((*CR >> ((7 - BA) * 4)) & 0xF ^ ((*CR >> ((7 - BB) * 4)) & 0xF)) & 0xF;
                setCRField(CR, BF, result);
            }

            // Emulates the crnand instruction
            void CRNAND(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB) {
                uint32_t result = ~((*CR >> ((7 - BA) * 4)) & 0xF & ((*CR >> ((7 - BB) * 4)) & 0xF)) & 0xF;
                setCRField(CR, BF, result);
            }

            // Emulates the crnor instruction
            void CRNOR(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB) {
                uint32_t result = ~((*CR >> ((7 - BA) * 4)) & 0xF | ((*CR >> ((7 - BB) * 4)) & 0xF)) & 0xF;
                setCRField(CR, BF, result);
            }

            // Emulates the cror instruction
            void CROR(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB) {
                uint32_t result = ((*CR >> ((7 - BA) * 4)) & 0xF) | ((*CR >> ((7 - BB) * 4)) & 0xF);
                setCRField(CR, BF, result);
            }

            // Emulates the crorc instruction
            void CRORC(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB) {
                uint32_t result = ((*CR >> ((7 - BA) * 4)) & 0xF) | ~((*CR >> ((7 - BB) * 4)) & 0xF);
                setCRField(CR, BF, result);
            }

            // Emulates the crxor instruction
            void CRXOR(uint32_t* CR, uint32_t BF, uint32_t BA, uint32_t BB) {
                uint32_t result = ((*CR >> ((7 - BA) * 4)) & 0xF) ^ ((*CR >> ((7 - BB) * 4)) & 0xF);
                setCRField(CR, BF, result);
            }

            // Emulates the mcrf instruction
            void MCRF(uint32_t* CR, uint32_t BF, uint32_t BFA) {
                uint32_t value = (*CR >> ((7 - BFA) * 4)) & 0xF;
                setCRField(CR, BF, value);
            }

            // Emulates the mcrfs instruction
            void MCRFS(uint32_t* CR, uint32_t* FPSCR, uint32_t BF, uint32_t BFA) {
                uint32_t value = (*FPSCR >> ((7 - BFA) * 4)) & 0xF;
                setCRField(CR, BF, value);
            }

            // Emulates the mtcrf instruction
            void MTCRF(uint32_t* CR, uint32_t CRM, uint32_t value) {
                for (int i = 0; i < 8; ++i) {
                    if (CRM & (1 << (7 - i))) {
                        setCRField(CR, i, (value >> ((7 - i) * 4)) & 0xF);
                    }
                }
            }

            // Emulates the mtocrf instruction
            void MTOCRF(uint32_t* CR, uint32_t CRM, uint32_t value) {
                // This function is typically a PowerPC Book E extension and not standard; similar to MTCRF
                MTCRF(CR, CRM, value);
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_SYSTEM_CALLS.h>

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the sc instruction
            void SC(uint32_t* registers, uint64_t* MSR, uint32_t* PC, void (*systemCallHandler)(uint32_t* registers, uint64_t* MSR)) {
                // Invoke the system call handler
                systemCallHandler(registers, MSR);

                // In a real system, the PC would be set to a system call handler routine
                // Here, we simulate advancing the PC to the next instruction
                *PC += 4; // Assuming PC points to the current instruction, advance to next
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

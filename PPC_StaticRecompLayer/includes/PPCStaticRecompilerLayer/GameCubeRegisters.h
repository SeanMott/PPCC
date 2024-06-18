#ifndef GAMECUBE_REGISTERS_H
#define GAMECUBE_REGISTERS_H

#include <cstdint>
#include <cstring> // for memset
#include <iostream>

constexpr int r0 = 0;
constexpr int r1 = 1;
constexpr int r2 = 2;
constexpr int r3 = 3;
constexpr int r4 = 4;
constexpr int r5 = 5;
constexpr int r6 = 6;
constexpr int r7 = 7;
constexpr int r8 = 8;
constexpr int r9 = 9;
constexpr int r10 = 10;
constexpr int r11 = 11;
constexpr int r12 = 12;
constexpr int r13 = 13;
constexpr int r14 = 14;
constexpr int r15 = 15;
constexpr int r16 = 16;
constexpr int r17 = 17;
constexpr int r18 = 18;
constexpr int r19 = 19;
constexpr int r20 = 20;
constexpr int r21 = 21;
constexpr int r22 = 22;
constexpr int r23 = 23;
constexpr int r24 = 24;
constexpr int r25 = 25;
constexpr int r26 = 26;
constexpr int r27 = 27;
constexpr int r28 = 28;
constexpr int r29 = 29;
constexpr int r30 = 30;
constexpr int r31 = 31;
constexpr int r32 = 32;
constexpr int r33 = 33;
constexpr int r34 = 34;
constexpr int r35 = 35;
constexpr int r36 = 36;
constexpr int r37 = 37;
constexpr int r38 = 38;
constexpr int r39 = 39;
constexpr int r40 = 40;

// Namespace for GameCube-related components
namespace GameCube {

    // General-purpose registers
    struct GeneralPurposeRegisters {
        uint32_t GPR[32];  // General-purpose registers (r0-r31)
    };

    // Floating-point registers
    struct FloatingPointRegisters {
        double FPR[32];    // Floating-point registers (f0-f31)
    };

    // Special-purpose registers (representative subset)
    struct SpecialPurposeRegisters {
        uint64_t SPR[1024];  // Example SPR array
        uint32_t LR;        // Link Register
        uint32_t CTR;       // Count Register
        uint64_t XER;       // Fixed-Point Exception Register
    };

    // Condition register
    struct ConditionRegister {
        uint32_t CR;        // Condition Register
    };

    // Segment registers
    struct SegmentRegisters {
        uint32_t SR[16];    // Segment Registers
    };

    // Machine State Register (MSR)
    struct MachineStateRegister {
        uint64_t MSR;       // Machine State Register
    };

    // Time Base Register
    struct TimeBaseRegister {
        uint64_t TBR[4];    // Time Base Registers
    };

    // Save/Restore Registers
    struct SaveRestoreRegisters {
        uint64_t SRR0;      // Save/Restore Register 0
        uint64_t SRR1;      // Save/Restore Register 1
    };

    // Floating-Point Status and Control Register (FPSCR)
    struct FPSCR {
        uint64_t FPSCR;     // Floating-Point Status and Control Register
    };

    // GameCube specific I/O registers (example subset)
    struct IORegisters {
        uint32_t PI_STATUS_REG;    // Processor Interface Status Register
        uint32_t PI_DMA_ADDRESS;   // Processor Interface DMA Address
        uint32_t PI_DMA_LENGTH;    // Processor Interface DMA Length
        uint32_t DSP_CONTROL_REG;  // Digital Signal Processor Control Register
        uint32_t DSP_MAILBOX;      // DSP Mailbox Register
        // ... Add other I/O registers as needed
    };

    // Combined structure for all GameCube registers
    struct GameCubeRegisters {
        GeneralPurposeRegisters GPR;
        FloatingPointRegisters FPR;
        SpecialPurposeRegisters SPR;
        ConditionRegister CR;
        SegmentRegisters SR;
        MachineStateRegister MSR;
        TimeBaseRegister TBR;
        SaveRestoreRegisters SRR;
        FPSCR fpscr;
        IORegisters IO;
        uint8_t memory[8192]; // Example memory array
        uint32_t PC; // Program Counter (simulated)
    };

    // Utility functions for managing and accessing GameCube registers

    // Function to reset all registers
    void resetRegisters(GameCubeRegisters& regs) {
        std::memset(&regs, 0, sizeof(GameCubeRegisters));
    }

    // Function to print register values (for debugging)
    void printRegisters(const GameCubeRegisters& regs) {
        // Print GPRs
        for (int i = 0; i < 32; ++i) {
            std::cout << "GPR[" << i << "] = 0x" << std::hex << regs.GPR.GPR[i] << std::endl;
        }

        // Print FPRs
        for (int i = 0; i < 32; ++i) {
            std::cout << "FPR[" << i << "] = " << std::dec << regs.FPR.FPR[i] << std::endl;
        }

        // Print SPRs
        std::cout << "LR = 0x" << std::hex << regs.SPR.LR << std::endl;
        std::cout << "CTR = 0x" << std::hex << regs.SPR.CTR << std::endl;
        std::cout << "XER = 0x" << std::hex << regs.SPR.XER << std::endl;

        // Print Condition Register
        std::cout << "CR = 0x" << std::hex << regs.CR.CR << std::endl;

        // Print Segment Registers
        for (int i = 0; i < 16; ++i) {
            std::cout << "SR[" << i << "] = 0x" << std::hex << regs.SR.SR[i] << std::endl;
        }

        // Print Machine State Register
        std::cout << "MSR = 0x" << std::hex << regs.MSR.MSR << std::endl;

        // Print Time Base Registers
        for (int i = 0; i < 4; ++i) {
            std::cout << "TBR[" << i << "] = 0x" << std::hex << regs.TBR.TBR[i] << std::endl;
        }

        // Print Save/Restore Registers
        std::cout << "SRR0 = 0x" << std::hex << regs.SRR.SRR0 << std::endl;
        std::cout << "SRR1 = 0x" << std::hex << regs.SRR.SRR1 << std::endl;

        // Print FPSCR
        std::cout << "FPSCR = 0x" << std::hex << regs.fpscr.FPSCR << std::endl;

        // Print I/O Registers
        std::cout << "PI_STATUS_REG = 0x" << std::hex << regs.IO.PI_STATUS_REG << std::endl;
        std::cout << "PI_DMA_ADDRESS = 0x" << std::hex << regs.IO.PI_DMA_ADDRESS << std::endl;
        std::cout << "PI_DMA_LENGTH = 0x" << std::hex << regs.IO.PI_DMA_LENGTH << std::endl;
        std::cout << "DSP_CONTROL_REG = 0x" << std::hex << regs.IO.DSP_CONTROL_REG << std::endl;
        std::cout << "DSP_MAILBOX = 0x" << std::hex << regs.IO.DSP_MAILBOX << std::endl;
    }

} // namespace GameCube

#endif // GAMECUBE_REGISTERS_H

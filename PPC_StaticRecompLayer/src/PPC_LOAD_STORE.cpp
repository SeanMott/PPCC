#include <PPCStaticRecompilerLayer/PPC/StaticRecompile/PPC_LOAD_STORE.h>
#include <cstring> // for memcpy
#include <iostream> // for error handling and messages

namespace PPC {
    namespace StaticRecompile {
        namespace ASM {

            // Emulates the lbz instruction
            void LBZ(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                registers[rD] = memory[effectiveAddress];
            }

            // Emulates the lbzu instruction
            void LBZU(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                registers[rD] = memory[effectiveAddress];
                registers[rA] = effectiveAddress;
            }

            // Emulates the lbzx instruction
            void LBZX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                registers[rD] = memory[effectiveAddress];
            }

            // Emulates the lbzux instruction
            void LBZUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                registers[rD] = memory[effectiveAddress];
                registers[rA] = effectiveAddress;
            }

            // Emulates the lhz instruction (Load Halfword and Zero)
            void LHZ(GameCube::GameCubeRegisters& ctx, uint32_t rD, int16_t offset, uint32_t rA) {
                uint32_t effectiveAddress = ctx.GPR.GPR[rA] + offset;
                uint16_t value;

                // Ensure the effective address is within memory bounds
                if (effectiveAddress + sizeof(value) > sizeof(ctx.memory)) {
                    std::cerr << "LHZ: Address out of bounds" << std::endl;
                    return;
                }

                // Simulate loading value from memory
                std::memcpy(&value, ctx.memory + effectiveAddress, sizeof(value));
                ctx.GPR.GPR[rD] = value; // Zero-extend 16-bit value to 32-bit

                std::cout << "LHZ: Loaded 0x" << std::hex << value << " from address 0x" << effectiveAddress << " into r" << rD << std::endl;
            }

            // Emulates the lhzu instruction
            void LHZU(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                registers[rD] = *(uint16_t*)&memory[effectiveAddress];
                registers[rA] = effectiveAddress;
            }

            // Emulates the lhzu instruction
            void LHZX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                registers[rD] = *(uint16_t*)&memory[effectiveAddress];
            }

            // Emulates the lhux instruction
            void LHZUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                registers[rD] = *(uint16_t*)&memory[effectiveAddress];
                registers[rA] = effectiveAddress;
            }

            // Emulates the lha instruction
            void LHA(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                registers[rD] = static_cast<int16_t>(*(uint16_t*)&memory[effectiveAddress]);
            }

            // Emulates the lhau instruction
            void LHAU(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                registers[rD] = static_cast<int16_t>(*(uint16_t*)&memory[effectiveAddress]);
                registers[rA] = effectiveAddress;
            }

            // Emulates the lhax instruction
            void LHAX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                registers[rD] = static_cast<int16_t>(*(uint16_t*)&memory[effectiveAddress]);
            }

            // Emulates the lhaux instruction
            void LHAUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                registers[rD] = static_cast<int16_t>(*(uint16_t*)&memory[effectiveAddress]);
                registers[rA] = effectiveAddress;
            }

            // Emulates the lwz instruction (Load Word and Zero)
            void LWZ(GameCube::GameCubeRegisters& ctx, uint32_t rD, int16_t offset, uint32_t rA) {
                uint32_t effectiveAddress = ctx.GPR.GPR[rA] + offset;
                uint32_t value = 0;

                // Ensure the effective address is within memory bounds
                if (effectiveAddress + sizeof(value) > sizeof(ctx.memory)) {
                    std::cerr << "LWZ: Address out of bounds" << std::endl;
                    return;
                }

                // Simulate loading value from memory
                std::memcpy(&value, ctx.memory + effectiveAddress, sizeof(value));
                ctx.GPR.GPR[rD] = value; // Load value into register rD

                std::cout << "LWZ: Loaded 0x" << std::hex << value << " from address 0x" << effectiveAddress
                    << " into r" << rD << std::endl;
            }

            // Emulates the lwzu instruction
            void LWZU(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                registers[rD] = *(uint32_t*)&memory[effectiveAddress];
                registers[rA] = effectiveAddress;
            }

            // Emulates the lwzx instruction
            void LWZX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                registers[rD] = *(uint32_t*)&memory[effectiveAddress];
            }

            // Emulates the lwzux instruction
            void LWZUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                registers[rD] = *(uint32_t*)&memory[effectiveAddress];
                registers[rA] = effectiveAddress;
            }


            // Emulates the stb instruction
            void STB(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                memory[effectiveAddress] = static_cast<uint8_t>(registers[rS]);
            }

            // Emulates the stbu instruction
            void STBU(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                memory[effectiveAddress] = static_cast<uint8_t>(registers[rS]);
                registers[rA] = effectiveAddress;
            }

            // Emulates the stbx instruction
            void STBX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                memory[effectiveAddress] = static_cast<uint8_t>(registers[rS]);
            }

            // Emulates the stbux instruction
            void STBUX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                memory[effectiveAddress] = static_cast<uint8_t>(registers[rS]);
                registers[rA] = effectiveAddress;
            }

            // Emulates the sth instruction
            void STH(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                *(uint16_t*)&memory[effectiveAddress] = static_cast<uint16_t>(registers[rS]);
            }

            // Emulates the sthu instruction
            void STHU(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                *(uint16_t*)&memory[effectiveAddress] = static_cast<uint16_t>(registers[rS]);
                registers[rA] = effectiveAddress;
            }

            // Emulates the sthx instruction
            void STHX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                *(uint16_t*)&memory[effectiveAddress] = static_cast<uint16_t>(registers[rS]);
            }

            // Emulates the sthux instruction
            void STHUX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                *(uint16_t*)&memory[effectiveAddress] = static_cast<uint16_t>(registers[rS]);
                registers[rA] = effectiveAddress;
            }

            // Emulates the stw instruction (Store Word)
            void STW(uint32_t* registers, uint32_t value, int16_t offset, uint32_t rA, uint8_t* memory) {
                uint32_t effectiveAddress = registers[rA] + offset;
                // Simulate storing value into memory at effectiveAddress
                std::memcpy(memory + effectiveAddress, &value, sizeof(value));
                std::cout << "STW: Stored 0x" << std::hex << value << " at address 0x" << effectiveAddress << std::endl;
            }

            // Emulates the stwu instruction (Store Word with Update)
            void STWU(GameCube::GameCubeRegisters& ctx, uint32_t rS, int16_t offset, uint32_t rA) {
                uint32_t effectiveAddress = ctx.GPR.GPR[rA] + offset;
                uint32_t value = ctx.GPR.GPR[rS];

                // Ensure the effective address is within memory bounds
                if (effectiveAddress + sizeof(value) > sizeof(ctx.memory)) {
                    std::cerr << "STWU: Address out of bounds" << std::endl;
                    return;
                }

                // Simulate storing value into memory at effectiveAddress
                std::memcpy(ctx.memory + effectiveAddress, &value, sizeof(value));

                // Update rA with the new address
                ctx.GPR.GPR[rA] = effectiveAddress;

                std::cout << "STWU: Stored 0x" << std::hex << value << " at address 0x" << effectiveAddress << std::endl;
                std::cout << "STWU: Updated rA to 0x" << std::hex << ctx.GPR.GPR[rA] << std::endl;
            }

            // Emulates the stwx instruction
            void STWX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                *(uint32_t*)&memory[effectiveAddress] = registers[rS];
            }

            // Emulates the stwux instruction
            void STWUX(uint32_t* registers, uint8_t* memory, uint32_t rS, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                *(uint32_t*)&memory[effectiveAddress] = registers[rS];
                registers[rA] = effectiveAddress;
            }

            // Emulates the lwa instruction
            void LWA(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, int32_t offset) {
                uint32_t effectiveAddress = registers[rA] + offset;
                int32_t loadedValue = *(int32_t*)&memory[effectiveAddress];
                registers[rD] = static_cast<uint32_t>(loadedValue);
            }

            // Emulates the lwax instruction
            void LWAX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                int32_t loadedValue = *(int32_t*)&memory[effectiveAddress];
                registers[rD] = static_cast<uint32_t>(loadedValue);
            }

            // Emulates the lwaux instruction
            void LWAUX(uint32_t* registers, uint8_t* memory, uint32_t rD, uint32_t rA, uint32_t rB) {
                uint32_t effectiveAddress = registers[rA] + registers[rB];
                int32_t loadedValue = *(int32_t*)&memory[effectiveAddress];
                registers[rD] = static_cast<uint32_t>(loadedValue);
                registers[rA] = effectiveAddress;
            }

            // Emulates the li instruction (Load Immediate)
            void LI(GameCube::GameCubeRegisters& ctx, uint32_t rD, int32_t IMM) {
                ctx.GPR.GPR[rD] = IMM;

                std::cout << "LI: Loaded immediate 0x" << std::hex << IMM << " into r" << rD << std::endl;
            }

        } // namespace ASM
    } // namespace StaticRecompile
} // namespace PPC

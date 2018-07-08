#include "stdafx.h"

using namespace Core;

VMCore::VMCore()
{
}


VMCore::~VMCore()
{
	this->memory.clear();
}

void VMCore::AddToMemory(Core::Utils::Enums::Instructions easmInstruction, std::vector<Core::Utils::EsetVMArguments>* arguments, int deltaSize) {
    memoryAddress += deltaSize;
    Core::Utils::EsetAssembly easm;
	easm.address = memoryAddress;
	easm.arguments.assign((*arguments).begin(), (*arguments).end());
	easm.instruction = easmInstruction;
	this->memory.push_back(easm);
}

void VMCore::MemoryDump() {
	std::cout << "=======================MEMORY_DUMP======================" << std::endl;
	for (std::vector<Core::Utils::EsetAssembly>::iterator it = memory.begin(); it != memory.end(); ++it) {
		Core::Utils::EsetAssembly memory = *it;

		std::string instructionName;
		std::cout << "[";
		std::cout << std::setfill('0') << std::setw(16) << std::hex << memory.address;
		std::cout << "] ";
		switch (memory.instruction) {
			case Core::Utils::Enums::Instructions::mov:
				instructionName = "mov";
				break;
			case Core::Utils::Enums::Instructions::loadConst:
				instructionName = "loadConst";
				break;
			case Core::Utils::Enums::Instructions::add:
				instructionName = "add";
				break;
			case Core::Utils::Enums::Instructions::sub:
				instructionName = "sub";
				break;
			case Core::Utils::Enums::Instructions::div:
				instructionName = "div";
				break;
			case Core::Utils::Enums::Instructions::mod:
				instructionName = "mod";
				break;
			case Core::Utils::Enums::Instructions::mul:
				instructionName = "mul";
				break;			
			case Core::Utils::Enums::Instructions::compare:
				instructionName = "compare";
				break;
			case Core::Utils::Enums::Instructions::jump:
				instructionName = "jump";
				break;
			case Core::Utils::Enums::Instructions::jumpEqual:
				instructionName = "jumpEqual";
				break;
            case Core::Utils::Enums::Instructions::consoleRead:
                instructionName = "consoleRead";
                break;
			case Core::Utils::Enums::Instructions::consoleWrite:
				instructionName = "consoleWrite";
				break;
			case Core::Utils::Enums::Instructions::hlt:
				instructionName = "hlt";
				break;
            case Core::Utils::Enums::Instructions::call:
                instructionName = "call";
                break;
            case Core::Utils::Enums::Instructions::ret:
                instructionName = "ret";
                break;
		}
		
		std::cout << instructionName;

		if (memory.arguments.size() > 0) {
			std::cout << "(";
			for (int i = 0; i < memory.arguments.size(); i++) {
				if (memory.instruction == Core::Utils::Enums::Instructions::loadConst) {
					std::cout << "<reg->" << memory.arguments[i].regId << " ";
					std::cout << "size->" << memory.arguments[i].size << " ";
					std::cout << std::hex << "value->" << memory.arguments[i].value;
				}
				else if (memory.instruction == Core::Utils::Enums::Instructions::jump || memory.instruction == Core::Utils::Enums::Instructions::jumpEqual || memory.instruction == Core::Utils::Enums::Instructions::call || memory.instruction == Core::Utils::Enums::Instructions::ret) {
					if (i > 0) {
						continue;
					}
					std::cout << "<address->" << memory.arguments[i].value << " ";
					std::cout << "size->" << memory.arguments[i].size << " ";
				}
				else if (memory.instruction != Core::Utils::Enums::Instructions::hlt) {
					std::cout << "<reg->" << memory.arguments[i].regId << " ";
					std::cout << "size->" << memory.arguments[i].size << " ";
				}
			}
			std::cout << ")";
		}

		std::cout << std::endl;
	}
}

uint64_t GetValueWithAccessSize(Core::Utils::Enums::MemoryAccessSize memSize, uint64_t data) {
	if (memSize == Core::Utils::Enums::MemoryAccessSize::byte) {
		return (data & 0x000000FF);
	}
	else if (memSize == Core::Utils::Enums::MemoryAccessSize::word) {
		return (data & 0x0000FFFF);
	}
	else if (memSize == Core::Utils::Enums::MemoryAccessSize::dword) {
		return (data & 0x00FFFFFFFF);
	}
	return data;
}

void VMCore::MoveInstructionPtrToMemoryAdress(std::vector<Core::Utils::EsetAssembly>::iterator* instructionPtr, int32_t memoryAddress) {
    for (std::vector<Core::Utils::EsetAssembly>::iterator it = memory.begin(); it != memory.end(); ++it) {
        Core::Utils::EsetAssembly memory = *it;
        if (memory.address == memoryAddress) {
            *instructionPtr = it;
        }
    }
}

void VMCore::Run() {
	std::cout << "=======================EXECUTION======================" << std::endl;
	for (std::vector<Core::Utils::EsetAssembly>::iterator it = memory.begin(); it != memory.end(); ++it) {
		Core::Utils::EsetAssembly memory = *it;
        if (memory.instruction == Core::Utils::Enums::Instructions::mov) {
            //this->registers[memory.arguments[1].regId] = this->registers[memory.arguments[0].regId];
            //std::cout << "regID before MOV: " << memory.arguments[1].regId << " value: " << this->registers[memory.arguments[1].regId] << " ";
            this->registers[memory.arguments[1].regId] = GetValueWithAccessSize(memory.arguments[0].size, this->registers[memory.arguments[0].regId]);
            this->registers[memory.arguments[1].regId] = GetValueWithAccessSize(memory.arguments[1].size, this->registers[memory.arguments[1].regId]);
            //std::cout << "regID after MOV: " << memory.arguments[1].regId << " value: " << this->registers[memory.arguments[1].regId];
            //std::cout << std::endl;
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::loadConst) {
            this->registers[memory.arguments[0].regId] = memory.arguments[0].value;
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::add) {
            this->registers[memory.arguments[2].regId] = this->registers[memory.arguments[0].regId] + this->registers[memory.arguments[1].regId];
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::sub) {
            this->registers[memory.arguments[2].regId] = this->registers[memory.arguments[0].regId] - this->registers[memory.arguments[1].regId];
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::div) {
            this->registers[memory.arguments[2].regId] = this->registers[memory.arguments[0].regId] / this->registers[memory.arguments[1].regId];
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::mod) {
            this->registers[memory.arguments[2].regId] = this->registers[memory.arguments[0].regId] % this->registers[memory.arguments[1].regId];
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::mul) {
            this->registers[memory.arguments[2].regId] = this->registers[memory.arguments[0].regId] * this->registers[memory.arguments[1].regId];
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::compare) {
            if (this->registers[memory.arguments[0].regId] < this->registers[memory.arguments[1].regId]) {
                this->registers[memory.arguments[2].regId] = -1;
            }
            else if (this->registers[memory.arguments[0].regId] == this->registers[memory.arguments[1].regId]) {
                this->registers[memory.arguments[2].regId] = 0;
            }
            else {
                this->registers[memory.arguments[2].regId] = 1;
            }
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::jump) {
            MoveInstructionPtrToMemoryAdress(&it, memory.arguments[0].value);
            continue;
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::jumpEqual) {
            if (this->registers[memory.arguments[1].regId] == this->registers[memory.arguments[2].regId]) {
                MoveInstructionPtrToMemoryAdress(&it, memory.arguments[0].value);
                continue;
            }
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::consoleRead) {
            std::cin >> this->registers[memory.arguments[0].regId];
            this->registers[memory.arguments[0].regId] = GetValueWithAccessSize(memory.arguments[0].size, this->registers[memory.arguments[0].regId]);
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::consoleWrite) {
            int64_t value = GetValueWithAccessSize(memory.arguments[0].size, this->registers[memory.arguments[0].regId]);
#if _DEBUG
            std::cout << "[hex]: ";
#endif
            std::cout << std::setfill('0') << std::setw(16) << std::hex << value;
#if _DEBUG
            std::cout << " - [dec]: ";
            std::cout << std::dec << value;
#endif
            std::cout << std::endl;
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::hlt) {
            system("PAUSE");
            exit(0);
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::call) {
            //make stack frame
            MoveInstructionPtrToMemoryAdress(&it, memory.arguments[0].value);
            continue;
        }
        else if (memory.instruction == Core::Utils::Enums::Instructions::ret) {

        }
	}
}
#include "stdafx.h"

using namespace Core;
using namespace Core::Utils;

void Loader::parseArguments(std::string* opcode, std::vector<Core::Utils::EsetVMArguments>* arguments) {
	for(int i = 0; i<(*arguments).size(); i++)
	{
		if ((*arguments)[i].isMemoryAddress == true) 
		{
			std::string value = opcode->substr(0, 32);
			opcode->erase(0, 32);

			(*arguments)[i].size = Core::Utils::Enums::MemoryAccessSize::dword;
			(*arguments)[i].regId = -1;

			std::reverse(value.begin(), value.end());
			unsigned long long memoryAddress = std::bitset<32>(value).to_ullong();
			(*arguments)[i].value = memoryAddress;
		} 
		else 
		{
			std::string value = opcode->substr(0, 1);
			opcode->erase(0, 1);

			if (value == "0") {
				value = opcode->substr(0, 4);
				opcode->erase(0, 4);

				(*arguments)[i].size = Core::Utils::Enums::MemoryAccessSize::qword;
			}
			else {
				value = opcode->substr(0, 2);
				opcode->erase(0, 2);

				if (value == "00") {
					(*arguments)[i].size = Core::Utils::Enums::MemoryAccessSize::byte;
				}
				else if (value == "01") {
					(*arguments)[i].size = Core::Utils::Enums::MemoryAccessSize::dword;
				}
				else if (value == "10") {
					(*arguments)[i].size = Core::Utils::Enums::MemoryAccessSize::word;
				}
				else if (value == "11") {
					(*arguments)[i].size = Core::Utils::Enums::MemoryAccessSize::qword;
				}
				value = opcode->substr(0, 4);
				opcode->erase(0, 4);
			}

			std::reverse(value.begin(), value.end());
			unsigned long long registerId = std::bitset<4>(value).to_ullong();
			(*arguments)[i].regId = registerId;
		}
	}
}

void Loader::loadConst(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: loadConst" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 3);

	std::string value = opcode->substr(0, 64);
	std::reverse(value.begin(), value.end());
	opcode->erase(0, 64);

	std::vector<EsetVMArguments> arguments;
	EsetVMArguments argument;
	argument.value = std::bitset<64>(value).to_ullong();
	arguments.push_back(argument);

	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::loadConst, &arguments, delta);
}

void Loader::clear(int* bptr, std::string* instruction) {
	*bptr = 0;
	*instruction = "";
}

void Loader::mov(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: mov" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 3);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(2);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::mov, &arguments, delta);
}

void Loader::add(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: add" << std::endl;
#endif
    int delta = opcode->length();
    opcode->erase(0, 6);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(3);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::add, &arguments, delta);
}

void Loader::sub(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: sub" << std::endl;
#endif

    int delta = opcode->length();
	opcode->erase(0, 6);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(3);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::sub, &arguments, delta);
}

void Loader::div(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: div" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 6);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(3);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::div, &arguments, delta);
}

void Loader::mod(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: mod" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 6);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(3);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::mod, &arguments, delta);
}

void Loader::mul(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: mul" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 6);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(3);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::mul, &arguments, delta);
}

void Loader::compare(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: compare" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 5);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(3);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::compare, &arguments, delta);
}

void Loader::jump(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: jump" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 5);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(1);
	arguments[0].isMemoryAddress = true;

	parseArguments(opcode, &arguments);
    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::jump, &arguments, delta);
}

void Loader::jumpEqual(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: jumpEqual" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 5);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(3);
	arguments[0].isMemoryAddress = true;
	parseArguments(opcode, &arguments);
    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::jumpEqual, &arguments, delta);
}

void Loader::consoleRead(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: consoleRead" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 5);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(1);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::consoleRead, &arguments, delta);
}

void Loader::consoleWrite(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: consoleWrite" << std::endl;
#endif

    int delta = opcode->length();
	opcode->erase(0, 5);

	std::vector<EsetVMArguments> arguments;
	arguments.resize(1);
	parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::consoleWrite, &arguments, delta);
}

void Loader::hlt(std::string* opcode) {
#if _DEBUG 
	std::cout << "debug: hlt" << std::endl;
#endif
    int delta = opcode->length();
	opcode->erase(0, 5);
	std::vector<EsetVMArguments> arguments;

    delta = delta - opcode->length();

	this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::hlt, &arguments, delta);
}

void Loader::call(std::string* opcode) {
#if _DEBUG 
    std::cout << "debug: call" << std::endl;
#endif

    int delta = opcode->length();
    opcode->erase(0, 4);

    std::vector<EsetVMArguments> arguments;
    arguments.resize(1);
    arguments[0].isMemoryAddress = true;
    parseArguments(opcode, &arguments);

    delta = delta - opcode->length();

    this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::call, &arguments, delta);
}

void Loader::ret(std::string* opcode) {
#if _DEBUG 
    std::cout << "debug: ret" << std::endl;
#endif

    int delta = opcode->length();
    opcode->erase(0, 4);

    std::vector<EsetVMArguments> arguments;

    delta = delta - opcode->length();

    this->vmCore->AddToMemory(Core::Utils::Enums::Instructions::ret, &arguments, delta);
}

Loader::Loader(std::string opcode, VMCore* vm)
{
	this->vmCore = vm;

#if _DEBUG 
	std::cout << "=============LOADER===============" << std::endl;
	std::cout << "=============BYTECODE===============" << std::endl;
	std::cout << opcode << std::endl;
	std::cout << "=============OPERATIONS===============" << std::endl;
#endif

    int operationTickCount = 0;
	int bytePtr = 0;
	std::string instruction = "";
	do {
        if (bytePtr > opcode.length()) {
            break;
        }

		instruction += (char)opcode[bytePtr++];
        std::cout << "instruction: " << instruction << std::endl;

        if (instruction == "000") {
            mov(&opcode);
            clear(&bytePtr, &instruction);
        }
        else if (instruction == "001") {
			loadConst(&opcode);
			clear(&bytePtr, &instruction);
		} 
		else if (instruction == "010001") {
			add(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "010010") {
			sub(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "010011") {
			div(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "010100") {
			mod(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "010101") {
			mul(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "01100") {
			compare(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "01101") {
			jump(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "01110") {
			jumpEqual(&opcode);
			clear(&bytePtr, &instruction);
		}
		//ELSE OPCODES
		else if (instruction == "10010") {
			consoleRead(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "10011") {
			consoleWrite(&opcode);
			clear(&bytePtr, &instruction);
		}
		else if (instruction == "10110") {
			hlt(&opcode);
			clear(&bytePtr, &instruction);
		}
        else if (instruction == "1100") {
            call(&opcode);
            clear(&bytePtr, &instruction);
        }
        else if (instruction == "1101") {
            ret(&opcode);
            clear(&bytePtr, &instruction);
        }
	} while (opcode.size() > 0);
}

Loader::~Loader()
{
}
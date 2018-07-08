#pragma once
#include "stdafx.h"

namespace Core {
	class Loader
	{
	private:
		VMCore* vmCore;
		void parseArguments(std::string* opcode, std::vector<Core::Utils::EsetVMArguments>* arguments);
		void loadConst(std::string* opcode);
        void clear(int* bptr, std::string* instruction);
		void mov(std::string* opcode);
		void add(std::string* opcode);
		void sub(std::string* opcode);
		void div(std::string* opcode);
		void mod(std::string* opcode);
		void mul(std::string* opcode);
		void compare(std::string* opcode);
		void jump(std::string* opcode);
		void jumpEqual(std::string* opcode);
		//reszta  opcode
		void consoleRead(std::string* opcode);
		void consoleWrite(std::string* opcode);
		void hlt(std::string* opcode);
        void call(std::string* opcode);
        void ret(std::string* opcode);
	public:
		Loader(std::string opcode, VMCore* vm);
		~Loader();
	};
}

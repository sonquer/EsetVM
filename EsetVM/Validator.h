#pragma once

namespace Core
{
	namespace Utils {
		class Validator
		{
		private:
			EsetVMFileHeader fileHeader;
		public:
			Validator(char* filePathBuffer);
			~Validator();

			bool fileIsValid;
			std::string opcode;
			uint32_t dataSize();
		};
	}
}
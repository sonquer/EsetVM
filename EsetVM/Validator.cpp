#include "stdafx.h"
#include "Validator.h"

using namespace Core::Utils;

Validator::Validator(char* filePathBuffer)
{
	std::ifstream file;
	file.open(filePathBuffer);
	if (!file.is_open())
	{
		this->fileIsValid = false;
		return;
	}

	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<uint8_t> fileBytes(fileSize, 0);
	file.read((char*)&fileBytes[0], fileSize);

	if (fileBytes.size() < sizeof(Core::Utils::EsetVMFileHeader)) {
		this->fileIsValid = false;
		return;
	}

	memcpy(&this->fileHeader.magic, fileBytes.data(), 8);
	if (!Helpers::ArrayComparer((char*)this->fileHeader.magic, 8, (char*)"ESET-VM2", 8)) {
		this->fileIsValid = false;
		return;
	}

	memcpy(&this->fileHeader.codeSize, fileBytes.data() + 8, 4); // copy code size
	memcpy(&this->fileHeader.dataSize, fileBytes.data() + 12, 4); // copy data size
	memcpy(&this->fileHeader.initialDataSize, fileBytes.data() + 16, 4); // copy initialDataSize

#if _DEBUG
	printf("codeSize=%d\n", this->fileHeader.codeSize);
	printf("dataSize=%d\n", this->fileHeader.dataSize);
	printf("initialDataSize=%d\n", this->fileHeader.initialDataSize);
	puts("");
#endif

	if (this->fileHeader.dataSize < this->fileHeader.initialDataSize) {
		this->fileIsValid = false;
		return;
	}

	size_t expectedFileSize = this->fileHeader.codeSize + this->fileHeader.initialDataSize + sizeof(Core::Utils::EsetVMFileHeader);
	
	if (expectedFileSize != fileSize) {
		this->fileIsValid = false;
		return;
	}

	int byte = 0;
	this->opcode = "";
	for (std::vector<uint8_t>::iterator it = fileBytes.begin(); it != fileBytes.end(); ++it, ++byte) {
		if (byte < sizeof(Core::Utils::EsetVMFileHeader)) {
			continue;
		}
		this->opcode += std::bitset<8>(*it).to_string();
	}

	this->fileIsValid = true;
}

uint32_t Validator::dataSize() {
	return this->fileHeader.dataSize;
}

Validator::~Validator()
{
}
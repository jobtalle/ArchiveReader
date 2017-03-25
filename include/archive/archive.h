#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

class Archive
{
public:
	Archive(const std::string path);
	~Archive();

private:
	enum flags {
		BATCH = 0x01,
		CLEAN = 0x02
	};

	struct entry {
		std::string name;
		uint64_t offset;
	};

	uint8_t flags;
	std::vector<entry> entries;
	std::vector<char> payload;

	void readFlags(std::ifstream &in);
	void readEntries(std::ifstream &in);
};
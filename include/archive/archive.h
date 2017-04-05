#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

#include "archiveFile.h"

class Archive
{
public:
	Archive(const std::string path);
	~Archive();

	bool exists(const std::string name) const;
	ArchiveFile getFile(const std::string name) const;
	size_t getFileSize(const std::string name) const;

private:
	enum flags {
		BATCH = 0x01,
		CLEAN = 0x02
	};

	struct entry {
		entry(){}
		entry(const std::string name)
		{
			this->name = name;
		}

		std::string name;
		uint64_t offset;
		uint64_t size;

		bool operator < (const struct entry &entry) const
		{
			return name.compare(entry.name) < 0;
		}
	};

	uint8_t flags;
	std::vector<entry> entries;
	std::vector<char> payload;

	void readFlags(std::ifstream &in);
	void readBody(std::ifstream &in);
	size_t readStringTab(std::vector<char> bytes);
};
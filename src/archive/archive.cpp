#include "archive/archive.h"
#include "archive/archiveFileStatic.h"
#include "archive/archiveFileDynamic.h"
#include "archive/archiveFileInvalid.h"
#include "miniz/miniz.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>

Archive::Archive(const std::string path)
:payload(nullptr)
{
	std::ifstream source(path, std::ios::binary);

	if(!source)
		throw std::invalid_argument("File not found");
	else
	{
		readFlags(source);
		readBody(source);

		source.close();
	}
}

Archive::~Archive()
{
	
}

bool Archive::exists(const std::string name) const
{
	if(std::lower_bound(entries.begin(), entries.end(), entry(name))->name.compare(name) != 0)
		return false;

	return true;
}

ArchiveFile Archive::getFile(const std::string name) const
{
	auto match = std::lower_bound(entries.begin(), entries.end(), entry(name));
	
	if(match->name.compare(name) != 0)
		return ArchiveFileInvalid();

	if(flags & BATCH)
	{
		return ArchiveFileStatic(name, payload, match->offset);
	}
	else
	{
		return ArchiveFileInvalid();
	}
}

size_t Archive::getFileSize(const std::string name) const
{
	auto match = std::lower_bound(entries.begin(), entries.end(), entry(name));

	if(match->name.compare(name) != 0)
		return 0;

	return (size_t)match->size;
}

void Archive::readFlags(std::ifstream &in)
{
	in.read((char*)&flags, sizeof(flags));
}

void Archive::readBody(std::ifstream &in)
{
	if(flags & BATCH)
	{
		mz_ulong uncompressedSize;
		in.read((char*)&uncompressedSize, sizeof(uncompressedSize));

		std::vector<char> body((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));
		std::vector<char> uncompressed(uncompressedSize);
		
		mz_uncompress((unsigned char*)uncompressed.data(), &uncompressedSize, (unsigned char*)body.data(), (mz_ulong)body.size());
		payload = std::make_shared<std::vector<char>>(uncompressed.begin() + readStringTab(uncompressed), uncompressed.end());
	}
	else
	{

	}
}

size_t Archive::readStringTab(std::vector<char> bytes)
{
	size_t index = 0;
	uint64_t lastOffset = 0;

	while(bytes.data()[index])
	{
		entry newEntry;

		while(bytes.data()[index])
			newEntry.name += bytes.data()[index++];

		++index;
		newEntry.offset = *((uint64_t*)(bytes.data() + index));

		if(entries.size())
			entries.at(entries.size() - 1).size = newEntry.offset - lastOffset;
		lastOffset = newEntry.offset;
		
		entries.push_back(newEntry);
		index += sizeof(uint64_t);
	}

	entries.at(entries.size() - 1).size = *((uint64_t*)(bytes.data() + ++index));
	
	return index + sizeof(uint64_t);
}
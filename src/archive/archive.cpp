#include <archive/archive.h>
#include <miniz/miniz.h>

#include <stdexcept>
#include <iostream>

Archive::Archive(const std::string path)
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

void Archive::readFlags(std::ifstream &in)
{
	in.read((char*)&flags, sizeof(flags));
}

void Archive::readBody(std::ifstream &in)
{
	if(flags & BATCH)
	{
		mz_ulong uncompressedSize;

		// Read entire batch size
		in.read((char*)&uncompressedSize, sizeof(uncompressedSize));

		// Read & uncompress body
		std::vector<char> body((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));
		std::vector<char> uncompressed(uncompressedSize);
		
		mz_uncompress((unsigned char*)uncompressed.data(), &uncompressedSize, (unsigned char*)body.data(), (mz_ulong)body.size());

		size_t readIndex = readStringTab(uncompressed);

		for(const entry entry:entries)
			std::cout << entry.name << std::endl;
	}
	else
	{

	}
}

size_t Archive::readStringTab(std::vector<char> bytes)
{
	size_t index = 0;
	uint64_t lastOffset = 0;

	while(bytes.data()[index] != '\0')
	{
		entry newEntry;

		while(bytes.data()[index] != '\0')
			newEntry.name += bytes.data()[index++];

		newEntry.offset = *((uint64_t*)(bytes.data() + index));

		if(entries.size())
			entries.at(entries.size() - 1).size = newEntry.offset - lastOffset;
		lastOffset = newEntry.offset;

		entries.push_back(newEntry);
		index += sizeof(uint64_t) + 1;
	}

	entries.at(entries.size() - 1).size = *((uint64_t*)(bytes.data() + index));
	
	return index + 5;
}
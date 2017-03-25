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
		readEntries(source);

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

void Archive::readEntries(std::ifstream &in)
{
	if(flags & BATCH)
	{

	}
	else
	{

	}
}
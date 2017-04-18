#include <archive/archiveFile.h>
#include <iostream>
ArchiveFile::ArchiveFile() {}

ArchiveFile::ArchiveFile(const std::string name)
:name(name) {}

ArchiveFile::~ArchiveFile() {}

std::string ArchiveFile::getName() const
{
	return name;
}

bool ArchiveFile::isValid() const
{
	return false;
}

const char *ArchiveFile::getBytes() const
{
	return nullptr;
}
#include <archive/archiveFile.h>

ArchiveFile::ArchiveFile() {}

ArchiveFile::ArchiveFile(const std::string name)
:name(name) {}

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
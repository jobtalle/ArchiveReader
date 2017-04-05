#include <archive/archiveFileStatic.h>

ArchiveFileStatic::ArchiveFileStatic(const std::string name, const char *bytes)
:ArchiveFile(name), bytes(bytes) {};

bool ArchiveFileStatic::isValid() const
{
	return true;
}

const char *ArchiveFileStatic::getBytes() const
{
	return bytes;
}
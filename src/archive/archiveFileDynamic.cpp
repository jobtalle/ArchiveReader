#include <archive/archiveFileDynamic.h>

ArchiveFileDynamic::ArchiveFileDynamic(const std::string name, char *bytes)
:ArchiveFile(name), bytes(bytes) {}

bool ArchiveFileDynamic::isValid() const
{
	return true;
}

const char *ArchiveFileDynamic::getBytes() const
{
	return bytes.get();
}
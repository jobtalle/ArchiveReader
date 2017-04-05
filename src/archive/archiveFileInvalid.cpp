#include <archive/archiveFileInvalid.h>

bool ArchiveFileInvalid::isValid() const
{
	return false;
}

const char *ArchiveFileInvalid::getBytes() const
{
	return nullptr;
}
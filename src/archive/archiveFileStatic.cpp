#include <archive/archiveFileStatic.h>

ArchiveFileStatic::ArchiveFileStatic(const std::string name, const std::shared_ptr<std::vector<char>> &payload, const size_t offset)
	:ArchiveFile(name), payload(payload), offset(offset) {};

bool ArchiveFileStatic::isValid() const
{
	return true;
}

const char *ArchiveFileStatic::getBytes() const
{
	return payload.get()->data() + offset;
}
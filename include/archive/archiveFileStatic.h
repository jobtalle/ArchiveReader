#include "archiveFile.h"

class ArchiveFileStatic : public ArchiveFile
{
public:
	ArchiveFileStatic(const std::string name, const char *bytes);
	bool isValid() const;
	const char *getBytes() const;

private:
	const char *bytes;
};
#include "archiveFile.h"

class ArchiveFileInvalid : public ArchiveFile
{
public:
	bool isValid() const;
	const char *getBytes() const;
};
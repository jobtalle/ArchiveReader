#include "archiveFile.h"

class ArchiveFileInvalid : public ArchiveFile
{
public:
	bool isValid() const override;
	const char *getBytes() const override;
};
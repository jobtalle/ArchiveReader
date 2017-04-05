#include "archiveFile.h"

#include <memory>

class ArchiveFileDynamic : public ArchiveFile
{
public:
	ArchiveFileDynamic(const std::string name, char *bytes);
	bool isValid() const;
	const char *getBytes() const;

private:
	std::shared_ptr<char> bytes;
};
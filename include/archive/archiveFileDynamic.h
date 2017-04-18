#include "archiveFile.h"

#include <memory>

class ArchiveFileDynamic : public ArchiveFile
{
public:
	ArchiveFileDynamic(const std::string name, char *bytes);
	bool isValid() const override;
	const char *getBytes() const override;

private:
	std::shared_ptr<char> bytes;
};
#include "archiveFile.h"

#include <vector>
#include <memory>

class ArchiveFileStatic : public ArchiveFile
{
public:
	ArchiveFileStatic(const std::string name, const std::shared_ptr<std::vector<char>> &payload, const size_t offset);
	bool isValid() const override;
	const char *getBytes() const override;

private:
	const std::shared_ptr<std::vector<char>> payload;
	const size_t offset;
};
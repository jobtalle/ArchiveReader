#pragma once

#include <string>

class ArchiveFile
{
public:
	ArchiveFile();
	ArchiveFile(const std::string name);
	virtual ~ArchiveFile();
	std::string getName() const;
	virtual bool isValid() const;
	virtual const char *getBytes() const;

private:
	std::string name;
};
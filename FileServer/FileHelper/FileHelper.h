#include <dirent.h>
#include <iostream>
#include <set>
#include <cstdio>

class FileHelper
{
public:
    FileHelper(std::string rootDir);
    ~FileHelper();
    void GetDirectoryContent(const std::string& targetDir);
    bool DeleteFile(const std::string& targetFile);
private:
    std::string m_rootDir;
    DIR *m_targetDir;
    struct dirent *m_directoryStruct;

    std::set<std::string> GetDirectoryContentList(const std::string& targetDir);
};

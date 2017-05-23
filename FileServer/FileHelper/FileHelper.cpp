#include "FileHelper.h"

using namespace std;

FileHelper::FileHelper(std::string rootDir)
        : m_rootDir(rootDir)
{
    if((m_targetDir = opendir(m_rootDir.data())) == NULL)
    {
        throw invalid_argument("Directory is not found");
    }
}

FileHelper::~FileHelper()
{
    closedir(m_targetDir);
}

std::set<std::string> FileHelper::GetDirectoryContent(const std::string& targetDir)
{
    set<string> contentSet;
    std::set<int>::iterator it;

    while ((m_directoryStruct = readdir(m_targetDir)))
    {
        contentSet.insert(std::move(m_directoryStruct->d_name));
    }

    return contentSet;
}

bool FileHelper::DeleteFile(const std::string& targetFile)
{
    return (std::remove(targetFile.data()) == 0) ? true : false;
}

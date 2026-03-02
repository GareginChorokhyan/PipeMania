#include "FileSystem.hpp"

const std::string FileSystem::path = "PipeMania/Other/";

FileSystem::Info FileSystem::read(const std::string &fileName)
{
    Info text;
    std::fstream file;
    file.open(path + fileName, std::ios::in);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if(!line.empty())
                text.push_back(stoi(line));
        }
        file.close();
    }

    return text;
}

void FileSystem::write(const Info &text, const std::string &fileName)
{
    std::fstream file;
    file.open(path + fileName, std::ios::out);

    if (file.is_open())
    {
        for (const auto &line : text)
        {
            file << line << std::endl;
        }
        file.close();
    }
}
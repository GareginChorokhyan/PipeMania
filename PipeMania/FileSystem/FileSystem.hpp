#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include <fstream>
#include <string>
#include <vector>

class FileSystem
{
private:
    static const std::string path;

public:
    using Info = std::vector<int>;

    static Info read(const std::string &fileName);
    static void write(const Info &, const std::string &fileName);

};

#endif // FILE_SYSTEM_HPP
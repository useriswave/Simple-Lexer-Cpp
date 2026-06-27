#include "../../includes/filereader.h"

#include <filesystem>
#include <fstream>
#include <iostream>

bool checkExtension(std::string_view path)
{
    std::filesystem::path file{ path };
    return file.extension() == ".dumblang";
}

std::string FileReader::readFile(const std::string& path)
{
    if (!checkExtension(path)) {
        throw std::runtime_error{ "ERROR: Unknown file extension. please ensure its .dumblang\n" };
    }

    std::ifstream reader{ path };

    if (!reader) {
        throw std::runtime_error{ "ERROR: file doesn't exist: '" + path + "'"};
    }

    std::string buffer{};
    std::string code{};

    while (getline(reader, buffer)) {
        code += buffer + '\n' ;
    }

    reader.close();
    return code;
}

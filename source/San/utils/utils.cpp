//
// Created by 秋鱼 on 2022/6/9.
//

#include "utils.hpp"

namespace San {

std::string_view GetFileExtension(std::string_view fileName)
{
    return fileName.substr(fileName.rfind('.')).substr(1);
}

std::string_view GetFileName(std::string_view fullName)
{
    auto base = fullName.substr(fullName.find_last_of("/\\") + 1);

    const auto p = base.find_last_of('.');
    if (p > 0 && p != std::string::npos) {
        base = base.substr(0, p);
    }

    return base;
}

bool IsFileExist(std::string_view fileName)
{
    //return std::filesystem::exists(fileName);

    // fast check file if exists
    // https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
    struct stat buffer;
    return (stat(fileName.data(), &buffer) == 0);
}

} // namespace San

﻿//
// Created by 秋鱼 on 2022/6/9.
//

#include "utils.hpp"

namespace San {


std::string_view GetFileExtension(std::string_view fileName)
{
    return fileName.substr(fileName.rfind('.')).substr(1);
}

} // namespace San

//
// Created by 秋鱼 on 2022/5/26.
//

#pragma once

namespace Yuan {

inline std::string_view GetFileExtension(std::string_view fileName)
{
    return fileName.substr(fileName.rfind('.')).substr(1);
}

} // namespace Yuan
//
// Created by 秋鱼 on 2022/6/9.
//

#pragma once

namespace San {

std::string_view GetFileExtension(std::string_view fileName);

std::string_view GetFileName(std::string_view fullName);

bool IsFileExist(std::string_view fileName);

} // namespace San
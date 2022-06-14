//
// Created by 秋鱼 on 2022/6/14.
//

#pragma once

namespace San {

template<typename T>
inline T AlignUp(T val, T alignment)
{
    return (val + alignment - static_cast<T>(1)) & ~(alignment - static_cast<T>(1));
}

} // namespace San
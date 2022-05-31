//
// Created by 秋鱼 on 2022/5/8.
//

#pragma once

namespace filesystem {
class path;
class resolver;
}

#ifndef DEL_COPY_IN_CLASS
#define DEL_COPY_IN_CLASS(CLASS_NAME)                         \
        CLASS_NAME(const CLASS_NAME&) = delete;               \
        CLASS_NAME(CLASS_NAME&&) = delete;                    \
        CLASS_NAME& operator=(const CLASS_NAME&) = delete;    \
        CLASS_NAME& operator=(CLASS_NAME && )= delete;
#endif

namespace San {


} // namespace San
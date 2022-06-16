//
// Created by 秋鱼 on 2022/6/16.
//

#include "math_utils.hpp"
#include <fmt/format.h>

namespace San {

std::string CompensatedFloat::ToString() const {
    return fmt::format("[ CompensatedFloat v: {} err: {} ]", v, err);
}

std::string Interval::ToString() const
{
    return fmt::format("[ Interval [{}, {}] ]", low, high);
}

} // namespace San
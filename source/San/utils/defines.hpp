//
// Created by 秋鱼 on 2022/6/16.
//

#pragma once

namespace San {

#ifdef SAN_USE_GPU
#define SAN_CPU_GPU __host__ __device__
#define SAN_GPU __device__

#else
#define SAN_CPU_GPU
#define SAN_GPU

#endif

// Float Type Definitions
#ifdef SAN_FLOAT_AS_DOUBLE
using Float = double;
#else
using Float = float;
#endif

#ifdef SAN_FLOAT_AS_DOUBLE
using FloatBits = uint64_t;
#else
using FloatBits = uint32_t;
#endif  // SAN_FLOAT_AS_DOUBLE
static_assert(sizeof(Float) == sizeof(FloatBits), "Float and FloatBits must have the same size");

} // namespace San
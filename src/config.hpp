#pragma once
#include <cstdint>

struct Config
{
    using FloatType = double;

    static constexpr uint32_t  samples_count = 16;
    static constexpr FloatType julia_r       = static_cast<FloatType>(-0.8);
    static constexpr FloatType julia_i       = static_cast<FloatType>(0.156);
    static constexpr float     fade_time     = 2.0f;
    static constexpr uint32_t  max_iteration = 1000;
};
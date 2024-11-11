//
// Created by 59794 on 2024/11/11.
//
#pragma once

#include <cmath>
#include <cstdint>
#include <tuple>

namespace math {
    struct Time {
      uint16_t hour_;
      uint16_t minute_;
      uint16_t second_;
    };
    inline bool operator == (Time t1, Time t2){
      return std::tie(t1.hour_, t1.minute_, t1.second_) ==
        std::tie(t2.hour_, t2.minute_, t2.second_);
    }
}

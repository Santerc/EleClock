
//
// Created by LENOVO on 2024/10/27.
//

#pragma once

#include <time_math.h>
#include <cstdint>

namespace cretnas{



    class Timer {
    public:
        Timer(){
            time_.second_ = 0;
            time_.minute_ = 0;
            time_.hour_ = 0;
            stop_ = true;
        }

        ~Timer() = default;

        void Start();
        void Stop();

        void SetTime(math::Time time);
        math::Time GetTime() {
          return time_;
        }

        void Clear();

        uint8_t GetSecond() const;
        uint8_t GetMinute() const;
        uint8_t GetHour() const;

        void AddHour();
        void AddMinute();
        void AddSecond();

        void MinusHour();
        void MinusMinute();
        void MinusSecond();

        bool IsStop() const;
    private:
        math::Time time_ = {
          .hour_ = 0,
          .minute_ = 0,
          .second_ = 0

        };
        bool stop_;
    };
}
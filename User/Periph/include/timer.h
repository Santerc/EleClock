
//
// Created by LENOVO on 2024/10/27.
//

#pragma once

#include <cstdint>

namespace cretnas{

    struct Time {
      uint16_t hour_;
      uint16_t minute_;
      uint16_t second_;
    };

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

        void SetTime(uint8_t second, uint8_t minute, uint8_t hour);

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
        Time time_;
        bool stop_;
    };
}
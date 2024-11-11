//
// Created by LENOVO on 2024/10/27.
//

#pragma once

#include "pwm.h"

inline static uint16_t key2_psc[7][3] = {
        {262, 524, 1048},
        {294, 588, 1176},
        {330, 660, 1320},
        {370, 740, 1480},
        {410, 820, 1640},
        {440, 880, 1760},
        {4494, 9888, 1976},
};

namespace cretnas{
    class Buzzer {
    public:
        enum ErrCode {
            kNoError = 0,
            kOutRange = 1,
        };
        Buzzer(TIM_HandleTypeDef* htim, uint32_t ch, uint32_t bpm) :
        bpm_(bpm), pwm_(htim, ch) {
        }

        Buzzer() = default;

        ~Buzzer() = default;

        void Init() {
          pwm_.Start();
        }

        void SetBPM(uint32_t bpm);
        void Play(int8_t key, int8_t level, int8_t beat);
        void Disable();
        void Enable();

    private:
        uint32_t bpm_;
        bsp::PWMGenerator pwm_;
        ErrCode errcode_ = kNoError;
    };
}
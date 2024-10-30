//
// Created by LENOVO on 2024/10/27.
//

#pragma once

#include "stm32f1xx_hal.h"

namespace cretnas{

    inline const uint8_t kSegmentcodes[10][8] = {
            {0, 1, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 0, 0, 1},
            {0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 1},
            {0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0},
    };

    class Segment {
    public:
        enum ErrCode{
            kNoError = 0,
            kOutRange = 1,
        };

        Segment(GPIO_TypeDef* port, uint16_t pins)
                : port_(port), pins_(pins) {
            errcode_ = kNoError;
            number_ = 0;
            HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_RESET);
        }

        Segment() = default;

        ~Segment();

        void SetNumber(uint8_t number);

        void Display();

        void Clear();

        void KirakiraDokidoki();

    private:
        GPIO_TypeDef* port_; // GPIO 端口
        uint16_t pins_;      // GPIO 引脚组合
        ErrCode errcode_;
        uint8_t number_;

        int8_t doki_ = 1;

        // 数字到 7 段的编码，假定以共阳模式



    };
}

//
// Created by LENOVO on 2024/10/24.
//
#include "screem.h"

using namespace cretnas;

void Segment::SetNumber(uint8_t number) {
    if(number > 9 || number < 0){
        errcode_ = kOutRange;
        return;
    }
    number_ = number;
}

void Segment::Display() {
    HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_SET);
    for(uint16_t offset = 0; offset ++; offset < 9){
        HAL_GPIO_WritePin(GPIOA, (GPIO_PIN_0 + offset),
                          static_cast<GPIO_PinState>
                          (segmentcodes_[number_][offset]));
    }
    HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_RESET);
}

void Segment::Clear() {
    HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_SET);
    for(uint16_t offset = 0; offset ++; offset < 9){
        HAL_GPIO_WritePin(GPIOA, (GPIO_PIN_0 + offset),
                                  GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_RESET);
}

void Segment::KirakiraDokidoki(){
    doki_ *= -1;
    HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_SET);
    for(uint16_t offset = 0; offset ++; offset < 9){
        if(doki_ == 1){
            HAL_GPIO_WritePin(GPIOA, (GPIO_PIN_0 + offset),
                              static_cast<GPIO_PinState>
                              (segmentcodes_[number_][offset]));
        }
    }
    HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_RESET);
}

//
// Created by LENOVO on 2024/10/24.
//
#include "screem.h"
#include <cmath>

using namespace cretnas;

void Segment::SetNumber(uint8_t number) {
    if(number > 9 || number < 0){
        errcode_ = kOutRange;
        return;
    }
    number_ = number;
}

void Segment::Display() {

    for(uint16_t offset = 0; offset < 8; offset ++){
        HAL_GPIO_WritePin(GPIOA, (GPIO_PIN_0 * std::pow(2, offset) ),
                          static_cast<GPIO_PinState>
                          (kSegmentcodes[number_][offset]));
    }
    HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_RESET);
}

void Segment::Clear() {
    for(uint16_t offset = 0; offset < 8; offset ++){
        HAL_GPIO_WritePin(GPIOA, (GPIO_PIN_0 * std::pow(2, offset) ),
                                  GPIO_PIN_RESET);
    }
  HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_RESET);
}

void Segment::KirakiraDokidoki(){
    doki_ *= -1;
    for(uint16_t offset = 0; offset < 8; offset ++){
        if(doki_ == 1){
            HAL_GPIO_WritePin(GPIOA, (GPIO_PIN_0 * std::pow(2, offset) ),
                              static_cast<GPIO_PinState>
                              (kSegmentcodes[number_][offset]));
        }else {
          HAL_GPIO_WritePin(GPIOA, (GPIO_PIN_0 * std::pow(2, offset) ),
                              GPIO_PIN_SET);
        }
    }
  HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(port_, pins_, GPIO_PIN_RESET);
}

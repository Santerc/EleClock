//
// Created by LENOVO on 2024/10/24.
//
#include "pwm.h"

using namespace bsp;

void PWMGenerator::Start() {
    if (state_ == PWM_State::kOff) {
        HAL_TIM_PWM_Start(htim_, channel_);
        state_ = PWM_State::kOn;
    }
}
void PWMGenerator::Stop() {
    if (state_ == PWM_State::kOn) {
        HAL_TIM_PWM_Stop(htim_, channel_);
        state_ = PWM_State::kOff;
    }
}
void PWMGenerator::SetDuty(float duty) {

    duty_ = duty;

}

void PWMGenerator::Output(){
    if(state_ == PWM_State::kOn){
        __HAL_TIM_SetCompare(htim_, channel_, duty_ * htim_->Init.Period);
    }
}

void PWMGenerator::Init() {
    HAL_TIM_PWM_Start(htim_,channel_);
    SetDuty(0);
}
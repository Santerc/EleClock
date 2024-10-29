//
// Created by LENOVO on 2024/10/24.
//
#include "buzzer.h"

using namespace cretnas;

void Buzzer::SetBPM(uint32_t bpm){
    bpm_ = bpm;
}

void Buzzer::Play(int8_t key, int8_t level, int8_t beat){
    pwm_.SetPsc(key2_psc[key][level]);
    pwm_.Output();
    HAL_Delay(1/8 * beat * 60 *1000 / bpm_);
}

void Buzzer::Disable(){
    pwm_.Stop();
}

void Buzzer::Enable(){
    pwm_.Start();
}
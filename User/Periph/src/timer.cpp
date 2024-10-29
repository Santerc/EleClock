//
// Created by LENOVO on 2024/10/24.
//
#include "timer.h"

using namespace cretnas;


void Timer::Start(){
    stop_ = false;
}

void Timer::Stop(){
    stop_ = true;
}


void Timer::SetTime(uint8_t second, uint8_t minute, uint8_t hour){
    hour_ = hour;
    second_ = second;
    minute_ = minute;
}


void Timer::Clear(){
    hour_ = 0;
    second_ = 0;
    minute_ = 0;
}


uint8_t Timer::GetSecond() const{
    return second_;
}

uint8_t Timer::GetMinute() const{
    return minute_;
}

uint8_t Timer::GetHour() const{
    return hour_;
}


void Timer::AddHour(){
    hour_ ++;
}

void Timer::AddMinute(){
    minute_ ++;
}

void Timer::AddSecond(){
    second_ ++;
}


void Timer::MinusHour(){
    hour_ --;
}

void Timer::MinusMinute(){
    minute_ --;
}

void Timer::MinusSecond(){
    second_ --;
}


bool Timer::IsStop() const{
    return stop_;
}
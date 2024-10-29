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
    if(hour_ == 24){
        hour_ = 0;
        stop_ = true;
    }
}

void Timer::AddMinute(){
    minute_ ++;
    if(minute_ == 60){
        AddHour();
        minute_ = 0;
    }
}

void Timer::AddSecond(){
    second_ ++;
    if(second_ == 60){
        AddMinute();
        second_ = 0;
    }
}


void Timer::MinusHour(){
    hour_ --;
    if(hour_ < 0) {
        hour_ = 23;
        stop_ = true;
    }
}

void Timer::MinusMinute(){
    minute_ --;
    if(minute_ < 0) {
        MinusHour();
        minute_ = 59;
    }
}

void Timer::MinusSecond(){
    second_ --;
    if(second_ < 0){
        MinusMinute();
        second_ = 59;
    }
}


bool Timer::IsStop() const{
    return stop_;
}
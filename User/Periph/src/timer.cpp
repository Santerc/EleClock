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


void Timer::SetTime(math::Time time){
    time_ = time;
}


void Timer::Clear(){
    time_.hour_ = 0;
    time_.second_ = 0;
    time_.minute_ = 0;
}


uint8_t Timer::GetSecond() const{
    return time_.second_;
}

uint8_t Timer::GetMinute() const{
    return time_.minute_;
}

uint8_t Timer::GetHour() const{
    return time_.hour_;
}


void Timer::AddHour(){
    time_.hour_ ++;
    if(time_.hour_ == 24){
        time_.hour_ = 0;
        stop_ = true;
    }
}

void Timer::AddMinute(){
    time_.minute_ ++;
    if(time_.minute_ == 60){
        AddHour();
        time_.minute_ = 0;
    }
}

void Timer::AddSecond(){
    time_.second_ ++;
    if(time_.second_ == 60){
        AddMinute();
        time_.second_ = 0;
    }
}


void Timer::MinusHour(){
    time_.hour_ --;
    if(time_.hour_ < 0) {
        time_.hour_ = 23;
        stop_ = true;
    }
}

void Timer::MinusMinute(){
    time_.minute_ --;
    if(time_.minute_ < 0) {
        MinusHour();
        time_.minute_ = 59;
    }
}

void Timer::MinusSecond(){
    time_.second_ --;
    if(time_.second_ < 0){
        MinusMinute();
        time_.second_ = 59;
    }
}




bool Timer::IsStop() const{
    return stop_;
}
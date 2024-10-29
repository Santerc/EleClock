#pragma once

#include "uart.h"

#define TERMINAL_RX_BUFFER_LEN 128

/*
 * Time   00:00:00\0
 * Alarm  00:00:00\0
 * */

class Terminal{
public:
    using Commend = enum{
      kSetTime = 0,
      kSetAlarm = 1,
    };



    Terminal()= default;
    ~Terminal();

    void Init(){
        uart_.InitDMA();
        uart_.ReceiveDMA(buffer_, TERMINAL_RX_BUFFER_LEN);
    }

    void Decode(uint8_t* buff, int rxdatalen){
        switch(buff[0]){
            case 'T':


        }

    }
private:
    bsp::Uart uart_;
    uint8_t buffer_[TERMINAL_RX_BUFFER_LEN];

    

};

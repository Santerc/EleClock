#pragma once

#include "uart.h"

#define TERMINAL_RX_BUFFER_LEN 128

namespace cretnas{
    /*
     * 0123456789012345
     * Time:00:00:00\0
     * Alarm:00:00:00\0
     * */

    class Terminal{
    public:
        using Commend = enum{
            kNull = 0,
            kSetTime = 1,
            kSetAlarm = 2,
            kError = 3,
        };



        Terminal(UART_HandleTypeDef *huart) {
            uart_ = bsp::Uart(huart);
            cmd_ = kNull;
            hour_ = 0;
            minute_ = 0;
            second_ = 0;
        }
        ~Terminal() = default;

        void Init(){
            uart_.InitDMA();
            uart_.ReceiveDMA(buffer_, TERMINAL_RX_BUFFER_LEN);
        }

        void Decode(uint8_t* buff, int rxdatalen){
            switch(rxdatalen){
                case 14:
                    cmd_ = kSetTime;
                    hour_ = (10 * buff[5] + buff[6]);
                    minute_ = (10 * buff[8] + buff[9]);
                    second_ = (10 * buff[11] + buff[12]);
                    break;
                case 15:
                    cmd_ = kSetAlarm;
                    hour_ = (10 * buff[6] + buff[7]);
                    minute_ = (10 * buff[9] + buff[10]);
                    second_ = (10 * buff[12] + buff[13]);
                    break;
                default:
                    cmd_ = kError;
                    break;

            }

        }

        void RxCallBack(){
            /* clear DMA transfer complete flag */
            uart_.DisableDMA();

            /* handle uart data from DMA */
            int Len = TERMINAL_RX_BUFFER_LEN - uart_.DMACurrentDataCounter();

            Decode(buffer_, Len);
            /* restart dma transmission */

            uart_.DMASetCounter(Len);
            uart_.EnableDMA();
        }

        Commend GetCmd() const{
            return cmd_;
        }

        uint16_t GetHour() const{
            return hour_;
        }

        uint16_t GetMinute() const{
            return minute_;
        }

        uint16_t GetSecond() const{
            return second_;
        }



    private:
        bsp::Uart uart_;
        uint8_t buffer_[TERMINAL_RX_BUFFER_LEN];
        Commend cmd_;
        uint16_t hour_;
        uint16_t minute_;
        uint16_t second_;


    };
}


#pragma once

#include "time_math.h"
#include "uart.h"
#include <iterator>

#define TERMINAL_RX_BUFFER_LEN 128

namespace cretnas {
/*
 * 0123456789012345
 * Time:00:00:00\0
 * Alarm:00:00:00\0
 * ShowAlarm\0
 * Delete:0\0
 * Help\0
 * */

class Terminal {
 public:
  using Commend = enum {
    kNull = 0,
    kSetTime = 1,
    kSetAlarm = 2,
    kDeleteAlarm = 3,
    kShowAlarm = 4,
    kError = 5,
  };

  Terminal(UART_HandleTypeDef* huart) {
    uart_ = bsp::Uart(huart);
    cmd_ = kNull;
    time_ = {.hour_ = 0, .minute_ = 0, .second_ = 0};
  }
  ~Terminal() = default;

  void Init() {
    uart_.InitDMA();
    uart_.ReceiveDMA(buffer_, TERMINAL_RX_BUFFER_LEN);
  }

  void Decode(uint8_t* buff, int rxdatalen) {
    switch (rxdatalen) {
      case 14:
        cmd_ = kSetTime;
        time_.hour_ = (10 * (buff[5] - '0') + (buff[6] - '0'));
        time_.minute_ = (10 * (buff[8] - '0') + (buff[9] - '0'));
        time_.second_ = (10 * (buff[11] - '0') + (buff[12] - '0'));
        break;
      case 15:
        cmd_ = kSetAlarm;
        time_.hour_ = (10 * (buff[6] - '0') + (buff[7] - '0'));
        time_.minute_ = (10 * (buff[9] - '0') + (buff[10] - '0'));
        time_.second_ = (10 * (buff[12] - '0') + (buff[13] - '0'));
        break;
      case 4:
        cmd_ = kNull;
        break;
      case 10:
        cmd_ = kShowAlarm;
        break;
      case 9:
        cmd_ = kDeleteAlarm;
      default:
        cmd_ = kError;
        break;
    }
  }

  void RxCallBack() {
    /* clear DMA transfer complete flag */
    uart_.DisableDMA();

    /* handle uart data from DMA */
    int Len = TERMINAL_RX_BUFFER_LEN - uart_.DMACurrentDataCounter();

    Decode(buffer_, Len);
    /* restart dma transmission */

    uart_.DMASetCounter(Len);
    uart_.EnableDMA();
  }

  void SendMsg(uint8_t const* msg) { uart_.SendMessage_IT(msg, sizeof(msg)); }

  Commend GetCmd() const { return cmd_; }

  math::Time GetTime() { return time_; }

 private:
  bsp::Uart uart_;
  uint8_t buffer_[TERMINAL_RX_BUFFER_LEN];
  Commend cmd_;
  math::Time time_;
};
}  // namespace cretnas

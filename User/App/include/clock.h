//
// Created by LENOVO on 2024/10/24.
//

#pragma once
#include "buzzer.h"
#include "main.h"
#include "screem.h"
#include "terminal.h"
#include "timer.h"
#include <functional>
#include <optional>
#include <vector>

typedef enum {
  kSecond = 0,
  kMinute = 1,
  kHour = 2
}position;
// position operator++(position& pos, int) {
//   pos = static_cast<position>((static_cast<int>(pos) + 1) % 3);
//   return pos;
// }
// position operator--(position& pos, int) {
//   pos = static_cast<position>((static_cast<int>(pos) + 2) % 3);
//   return pos;
// };

class Clock {
 public:
  Clock(UART_HandleTypeDef* huart,
        GPIO_TypeDef* gpio_hour_h, uint16_t hour_h_pin,
        GPIO_TypeDef* gpio_hour_l, uint16_t hour_l_pin,
        GPIO_TypeDef* gpio_min_h, uint16_t min_h_pin, GPIO_TypeDef* gpio_min_l,
        uint16_t min_l_pin, GPIO_TypeDef* gpio_second_h, uint16_t sec_h_pin,
        GPIO_TypeDef* gpio_second_l, uint16_t sec_l_pin)
      : terminal_(&huart1),
        conser_(position::kSecond) {
    alarm_times_ = std::vector<math::Time>();
    segment_[kHourHigh] = cretnas::Segment(gpio_hour_h, hour_h_pin);
    segment_[kHourLow] = cretnas::Segment(gpio_hour_l, hour_l_pin);
    segment_[kMinuteHigh] = cretnas::Segment(gpio_min_h, min_h_pin);
    segment_[kMinuteLow] = cretnas::Segment(gpio_min_l, min_l_pin);
    segment_[kSecondHigh] = cretnas::Segment(gpio_second_h, sec_h_pin);
    segment_[kSecondLow] = cretnas::Segment(gpio_second_l, sec_l_pin);

    timePlus_ = {[this]() { timer_.AddSecond(); },
                 [this]() { timer_.AddMinute(); },
                 [this]() { timer_.AddHour(); }};

    timeMinus_ = {[this]() { timer_.MinusSecond(); },
                  [this]() { timer_.MinusMinute(); },
                  [this]() { timer_.MinusHour(); }};
  }
  Clock() : terminal_(&huart1){};
  std::vector<std::function<void()>> timePlus_;
  std::vector<std::function<void()>> timeMinus_;

  void Init() {
    terminal_.Init();
        segment_[kSecondLow].Init();
        segment_[kSecondHigh].Init();
        segment_[kMinuteLow].Init();
        segment_[kMinuteHigh].Init();
        segment_[kHourLow].Init();
        segment_[kHourHigh].Init();
  }
  void TikTok() {
    timer_.AddSecond();
  }
  void ConserLeft() { conser_ = static_cast<position>((static_cast<int>(conser_) + 1)%3); }
  void ConserRight() { conser_ = static_cast<position>((static_cast<int>(conser_) + 2)%3); }


  void RxCallback() {
    // HAL_UART_Transmit_IT(&huart1, reinterpret_cast<uint8_t const*>("34\n"), 3);
    terminal_.RxCallBack();
  }

  bool isStop() const { return timer_.IsStop(); }

  void FinishCmd() {
    terminal_.FinishCmd();
  }
  void SendMsg(uint8_t const* msg) {
    terminal_.SendMsg(msg);
  }

  void Stop() { timer_.Stop(); }
  void Start() {
    timer_.Start();
    // buzzer_.SetBPM(60);
    // buzzer_.Play(1, 1, 1);
    // buzzer_.Play(2, 1, 1);
    // buzzer_.Play(3, 1, 1);
  }

  position GetCorser() const { return conser_; }

  void SetTime() {
    timer_.Stop();
    timer_.SetTime(terminal_.GetTime());

  }
  void ClearTime() {
    timer_.Stop();
    timer_.Clear();

  }

  void Hplus() {
    timer_.AddOnlyHour();
  }
  void Mplus() {
    timer_.AddOnlyMinute();
  }
  void Splus() {
    timer_.AddOnlySecond();
  }
  void HMinus() {
    timer_.MinusOnlyHour();
  }
  void MMinus() {
    timer_.MinusOnlyMinute();
  }
  void SMinus() {
    timer_.MinusOnlySecond();
  }

  bool isSetTime() const { return timeset_; }
  void SettingMode(bool const flag) {
    timeset_ = flag;
    if (!flag) {
      conser_ = position::kSecond;
    }
  }

  bool AlarmCheck() {
    for(int i = 0; i < alarm_times_.size(); i++) {
      if((timer_.GetTime() == alarm_times_[i]) &&
        !timer_.IsStop()) {
        return true;
      }
    }
    return false;
  }
  void AlarmAdd() {
    if (std::find(alarm_times_.begin(), alarm_times_.end(), terminal_.GetTime()) ==
        alarm_times_.end()) {
      alarm_times_.push_back(terminal_.GetTime());
    }
  }
  void AlarmDelete() {
    if (terminal_.GetId() < alarm_times_.size()) {
      alarm_times_.erase(alarm_times_.begin() + terminal_.GetId());
    } else {
      terminal_.SendMsg(reinterpret_cast<uint8_t const*>("Error id!\n"));
    }
  }
  void AlarmShow() {
    for (int id = 0; id < alarm_times_.size(); id++) {
      std::string message = "Alarm:" + std::to_string(id) +
                            std::to_string(timer_.GetHour()) + ":" +
                            std::to_string(timer_.GetMinute()) + ":" +
                            std::to_string(timer_.GetSecond()) + "\n";
      terminal_.SendMsg(reinterpret_cast<uint8_t const*>(message.c_str()));
    }
  }

  cretnas::Terminal::Commend GetCmd() {
    return terminal_.GetCmd();
  }

  void TubeSetNum() {
    segment_[kSecondLow].SetNumber(timer_.GetSecond() % 10);
    segment_[kSecondHigh].SetNumber(timer_.GetSecond() / 10);
    segment_[kMinuteLow].SetNumber(timer_.GetMinute() % 10);
    segment_[kMinuteHigh].SetNumber(timer_.GetMinute() / 10);
    segment_[kHourLow].SetNumber(timer_.GetHour() % 10);
    segment_[kHourHigh].SetNumber(timer_.GetHour() / 10);
  }
  void TubeDisplay() {
    if(timeset_) {
        for(int id = 0; id <= kHourHigh; id ++) {
          if((id/2) != static_cast<int>(conser_)) {
            segment_[id].Display();
          } else {
            segment_[id].KirakiraDokidoki();
          }
        }
    }else {
      segment_[kSecondLow].Display();
      segment_[kSecondHigh].Display();
      segment_[kMinuteLow].Display();
      segment_[kMinuteHigh].Display();
      segment_[kHourLow].Display();
      segment_[kHourHigh].Display();
    }
  }

 private:
  using cs = enum {
    kSecondLow = 0,
    kSecondHigh = 1,
    kMinuteLow = 2,
    kMinuteHigh = 3,
    kHourLow = 4,
    kHourHigh = 5
  };
  cretnas::Timer timer_;
  cretnas::Segment segment_[6];
  cretnas::Terminal terminal_;
  position conser_;
  bool timeset_ = false;
  std::vector<math::Time> alarm_times_;
};



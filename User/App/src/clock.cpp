//
// Created by LENOVO on 2024/10/24.
//
#include "buzzer.h"
#include "main.h"
#include "screem.h"
#include "terminal.h"
#include "timer.h"
#include <vector>
#include <functional>
#include <optional>

    enum class position{
        kSecond = 0,
        kMinute = 1,
        kHour = 2
    };
    position operator ++(position& pos, int) {
      return static_cast<position>((static_cast<int>(pos) + 1) % 3);
    }
    position operator --(position& pos, int) {
      return static_cast<position>((static_cast<int>(pos) + 2) % 3);
    };

class Clock{
public:
    Clock(UART_HandleTypeDef* huart,
          TIM_HandleTypeDef* hpwm, uint16_t channel,
          GPIO_TypeDef* gpio_hour_h, uint16_t hour_h_pin,
          GPIO_TypeDef* gpio_hour_l, uint16_t hour_l_pin,
          GPIO_TypeDef* gpio_min_h, uint16_t min_h_pin,
          GPIO_TypeDef* gpio_min_l, uint16_t min_l_pin,
          GPIO_TypeDef* gpio_second_h, uint16_t sec_h_pin,
          GPIO_TypeDef* gpio_second_l, uint16_t sec_l_pin) :
          buzzer_(hpwm, channel, 120),
          terminal_(huart)
          {
            segment_[kSecondLow] = cretnas::Segment(gpio_hour_h, hour_h_pin);
            segment_[kSecondHigh] = cretnas::Segment(gpio_hour_l, hour_l_pin);
            segment_[kMinuteLow] = cretnas::Segment(gpio_min_h, min_h_pin);
            segment_[kMinuteHigh] = cretnas::Segment(gpio_min_l, min_l_pin);
            segment_[kHourLow] = cretnas::Segment(gpio_second_h, sec_h_pin);
            segment_[kHourHigh] = cretnas::Segment(gpio_second_l, sec_l_pin);

            timePlus_ = {
              [this]() {timer_.AddHour();},
              [this]() {timer_.AddMinute();},
              [this]() {timer_.AddSecond();}
            };

            timeMinus_ = {
              [this]() {timer_.MinusHour();},
              [this]() {timer_.MinusMinute();},
              [this]() {timer_.MinusSecond();}
            };
          }
    Clock() = default;
    std::vector<std::function<void()>> timePlus_;
    std::vector<std::function<void()>> timeMinus_;
    void ConserLeft() {
      conser_ ++;
    }
    void ConserRight() {
      conser_ --;
    }

    void RxCallback() {
      terminal_.RxCallBack();
    }

    bool isStop() const {
      return timer_.IsStop();
    }

    void Stop() {
      timer_.Stop();
    }
    void Start() {
      timer_.Start();
      buzzer_.SetBPM(60);
      buzzer_.Play(1, 1, 1);
      buzzer_.Play(2, 1, 1);
      buzzer_.Play(3, 1, 1);
    }

    position GetCorser() const {
      return conser_;
    }

    void SetTime() {
      timer_.SetTime(terminal_.GetSecond(),
                    terminal_.GetMinute(),
                    terminal_.GetHour());
      timer_.Stop();
    }
    void ClearTime() {
      timer_.Clear();
      timer_.Stop();
    }

    bool isSetTime() const {
      return timeset_;
    }
    void SettingMode(bool const flag) {
      timeset_ = flag;
    }

    bool AlbumCheck() {
      if(timer_.GetHour() == )
    }

private:
    using cs = enum{
        kSecondLow = 0,
        kSecondHigh = 1,
        kMinuteLow = 2,
        kMinuteHigh = 3,
        kHourLow = 4,
        kHourHigh = 5
    };
    cretnas::Timer timer_;
    cretnas::Segment segment_[6];
    cretnas::Buzzer buzzer_;
    cretnas::Terminal terminal_;
    position conser_;
    bool timeset_ = false;

};

Clock eleclock(&huart1,
            &htim1, HAL_TIM_ACTIVE_CHANNEL_1,
            HOUR_T_CS_GPIO_Port, HOUR_T_CS_Pin,
            HOUR_O_CS_GPIO_Port, HOUR_O_CS_Pin,
            MIN_T_CS_GPIO_Port, MIN_T_CS_Pin,
            MIN_O_CS_GPIO_Port, MIN_O_CS_Pin,
            SEC_T_CS_GPIO_Port, SEC_T_CS_Pin,
            SEC_O_CS_GPIO_Port, SEC_O_CS_Pin);

/**
  * @brief      定时器中断回调函数
  * @param      htim: 指针指向定时器句柄
  * @retval     无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim == &htim2){
        if(!eleclock.isStop()){
            eleclock.timePlus_[static_cast<int>(position::kSecond)];
        }
    }
}


enum class GPIOPin : uint16_t {
  kRight = GPIO_PIN_12,
  kLeft = GPIO_PIN_11,
  kPlus = GPIO_PIN_15,
  kMinus = GPIO_PIN_14,
  kStartStop = GPIO_PIN_13,
  kSetting = GPIO_PIN_10,
};
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    switch(GPIO_Pin) {
      case GPIO_PIN_12:
        eleclock.ConserRight();
        break;
      case GPIO_PIN_11:
        eleclock.ConserLeft();
        break;
      case GPIO_PIN_15:
        if(eleclock.isSetTime()) {
          eleclock.timePlus_[static_cast<int>(eleclock.GetCorser())];
        }
        break;
      case GPIO_PIN_14:
        if(eleclock.isSetTime()) {
          eleclock.timeMinus_[static_cast<int>(eleclock.GetCorser())];
        }
        break;
      case GPIO_PIN_13:
        if(eleclock.isSetTime()) {
          eleclock.SettingMode(false);
        }else {
          eleclock.Start();
        }
        break;
      case GPIO_PIN_10:
        if(eleclock.isStop()) {
          eleclock.SettingMode(true);
        }else {
          eleclock.Stop();
        }
        break;
      default:
        break;

    }
}

/**
  * @brief      UART RX 回调分配函数
  * @param      huart: uart IRQHandler id
  * @retval     无
  */
void Uart_RxIdleCallback(UART_HandleTypeDef* huart) {
    if(huart == &huart1){
      eleclock.RxCallback();
    }
}


void Uart_ReceiveHandler(UART_HandleTypeDef *huart) {
    // clear idle it flag after uart receive a frame data
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE)
      && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE)) {
        /* clear idle it flag avoid idle interrupt all the time */
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        /* handle received data in idle interrupt */
        Uart_RxIdleCallback(huart);
    }
}
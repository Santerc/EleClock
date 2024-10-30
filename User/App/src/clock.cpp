//
// Created by LENOVO on 2024/10/24.
//
#include "timer.h"
#include "screem.h"
#include "buzzer.h"
#include "terminal.h"
#include "main.h"

namespace{
    using position = enum{
        kSecond = 0,
        kMinute = 1,
        kHour = 2
    };
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
          terminal_(huart),
          timer_()
          {
            segment_[kSecondLow] = cretnas::Segment(gpio_hour_h, hour_h_pin);
            segment_[kSecondHigh] = cretnas::Segment(gpio_hour_l, hour_l_pin);
            segment_[kMinuteLow] = cretnas::Segment(gpio_min_h, min_h_pin);
            segment_[kMinuteHigh] = cretnas::Segment(gpio_min_l, min_l_pin);
            segment_[kHourLow] = cretnas::Segment(gpio_second_h, sec_h_pin);
            segment_[kHourHigh] = cretnas::Segment(gpio_second_l, sec_l_pin);
          }
    Clock() = default;

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
};

/**
  * @brief      定时器中断回调函数
  * @param      htim: 指针指向定时器句柄
  * @retval     无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim == &htim2){
//        if(!timer.IsStop()){
//            timer.AddSecond();
//        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == GPIO_PIN_13){

    }
}

/**
  * @brief      UART RX 回调分配函数
  * @param      huart: uart IRQHandler id
  * @retval     无
  */
void Uart_RxIdleCallback(UART_HandleTypeDef* huart) {
    if(huart == &huart1){
//        terminal.RxCallBack();
    }
}


void Uart_ReceiveHandler(UART_HandleTypeDef *huart) {
    // clear idle it flag after uart receive a frame data
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE)) {
        /* clear idle it flag avoid idle interrupt all the time */
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        /* handle received data in idle interrupt */
        Uart_RxIdleCallback(huart);
    }
}
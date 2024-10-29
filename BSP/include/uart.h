//
// Created by LENOVO on 2024/10/22.
//
#pragma once

#include "main.h"
#include "stm32f103xb.h"
#include "usart.h"
#include "error.h"

namespace bsp{
    class Uart{
    public:
        Uart() = default;
        Uart(UART_HandleTypeDef* huart){
            huart_ = huart;
        }
        ~Uart();

        /**
          * @brief      初始化UART DMA
          * @param      NULL
          * @retval     NULL
          */
        void InitDMA();

        /**
          * @brief      向UART串口发送信息（阻塞模式）
          * @param      txdata: 要发送的信息
          * @param      size: 要发送信息的长度
          * @param      timeout: 超时时间
          * @retval     无
          */
        void SendMessage(uint8_t const* txdata, uint16_t size, uint32_t timeout);

        /**
          * @brief      向UART串口发送信息（非阻塞模式）
          * @param      txdata: 要发送的信息
          * @param      size: 要发送信息的长度
          * @retval     无
          */
        void SendMessage_IT(uint8_t const* txdata, uint16_t size);

        /**
          * @brief      向UART串口发送信息（非阻塞模式），强制等待，可能造成延时
          * @param      txdata: 要发送的信息
          * @param      size: 要发送信息的长度
          * @param      timeout: 超时时间
          * @retval     无
          */
        void SendMessage_IT_Force(uint8_t const* txdata, uint16_t size, uint32_t timeout);

        /**
          * @brief      enable global uart it and do not use DMA transfer done it
          * @param      huart: uart IRQHandler id
          * @param      pData: receive buff
          * @param      Size:  buff size
          * @retval     set success or fail
          */
        void ReceiveDMA(uint8_t rxdata[], uint32_t size);

        static uint16_t DMACurrentDataCounter(DMA_Channel_TypeDef *dma_stream) {
            /* Return the number of remaining data units for DMAy Streamx */
            return (static_cast<uint16_t>(dma_stream->CNDTR));
        }

    private:
        UART_HandleTypeDef* huart_;
    };
}


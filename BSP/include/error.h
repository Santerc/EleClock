//
// Created by LENOVO on 2024/10/24.
//
#pragma once

uint32_t uart_error_type = 0;

namespace bsp{
    inline void Uart_ErrorHandler(uint32_t ret){
        while (1) {
            uart_error_type = ret;
            return;
        }
    }
}



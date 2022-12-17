//
// Created by arekc on 17/12/2022.
//

#ifndef INC_429TESTS_CWRAPPERS_H
#define INC_429TESTS_CWRAPPERS_H

#include <i2c.h>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif


EXTERNC void uartReceiveGlobalCallback(UART_HandleTypeDef *huart);

#endif //INC_429TESTS_CWRAPPERS_H

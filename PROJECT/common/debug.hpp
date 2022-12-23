//
// Created by arekc on 16/10/2022.
//

#ifndef INC_429TESTS_DEBUG_HPP
#define INC_429TESTS_DEBUG_HPP

#include <cstring>
#include <cstdio>
#include <main.h>
#include "FreeRTOS.h"
#include <task.h>


#if defined NDEBUG
#define TRACE( format, ... )
#define TRACE(format)
#else

#define TRACE_INIT(file_name) static const char fn[] = #file_name; static TaskHandle_t xTaskToQuery;

#define TRACE_ARG(format, ...)                                                        \
{                                                                                     \
printf( "%s -> %s::%s(%d) " , pcTaskGetName(xTaskToQuery), fn, __FUNCTION__,  __LINE__);      \
printf(format, __VA_ARGS__); printf("\r\n");                                          \
}

#define TRACE(format)                                                                 \
{                                                                                     \
printf( "%s -> %s::%s(%d) " , pcTaskGetName(xTaskToQuery), fn, __FUNCTION__,  __LINE__);      \
printf(format); printf("\r\n");                                                       \
}

#endif


#endif //INC_429TESTS_DEBUG_HPP

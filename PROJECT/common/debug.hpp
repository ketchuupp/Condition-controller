//
// Created by arekc on 16/10/2022.
//

#ifndef INC_429TESTS_DEBUG_HPP
#define INC_429TESTS_DEBUG_HPP

#include "string.h"
#include <cstdio>
#include <main.h>



#if defined NDEBUG
#define TRACE( format, ... )
#define TRACE(format)
#else
//#define TRACE_ARG( format, ... )   printf( "%s::%s(%d) " __FILE__, __FUNCTION__,  __LINE__);      \
//printf(format, __VA_ARGS__); printf("\r\n")
//
//#define TRACE( format )   printf( "%s::%s(%d) " __FILE__, __FUNCTION__,  __LINE__); \
//printf(format); printf("\r\n")

#define TRACE_ARG( format, ... )   printf( "%s(%d) " ,__FUNCTION__,  __LINE__);      \
printf(format, __VA_ARGS__); printf("\r\n")

#define TRACE( format )   printf( "%s(%d) " ,__FUNCTION__,  __LINE__); \
printf(format); printf("\r\n")

#endif


#endif //INC_429TESTS_DEBUG_HPP

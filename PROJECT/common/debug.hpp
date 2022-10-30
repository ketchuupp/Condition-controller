//
// Created by arekc on 16/10/2022.
//

#ifndef INC_429TESTS_DEBUG_HPP
#define INC_429TESTS_DEBUG_HPP

#if defined NDEBUG
#define TRACE( format, ... )
#define TRACE(format)
#else
#define TRACE_ARG( format, ... )   printf( "%s::%s(%d) " format, __FILE__, __FUNCTION__,  __LINE__, __VA_ARGS__ )
#define TRACE( format )   printf( "%s::%s(%d) " format, __FILE__, __FUNCTION__,  __LINE__)
#endif


#endif //INC_429TESTS_DEBUG_HPP

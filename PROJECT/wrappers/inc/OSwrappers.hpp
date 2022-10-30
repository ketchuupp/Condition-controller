//
// Created by arekc on 15/10/2022.
//

#ifndef INC_429TESTS_OSWRAPPERS_HPP
#define INC_429TESTS_OSWRAPPERS_HPP

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void osStartApp();

#undef EXTERNC
#endif //INC_429TESTS_OSWRAPPERS_HPP

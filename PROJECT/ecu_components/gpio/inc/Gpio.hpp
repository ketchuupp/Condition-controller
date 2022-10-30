//
// Created by arekc on 16/10/2022.
//

#ifndef INC_429TESTS_GPIO_HPP
#define INC_429TESTS_GPIO_HPP

#include <gpio.h>


class Gpio {
    GPIO_TypeDef * m_port;
    uint16_t  m_pin;

public:
  Gpio(GPIO_TypeDef *port, uint16_t pin);
    void toggle();
};


#endif//INC_429TESTS_GPIO_HPP

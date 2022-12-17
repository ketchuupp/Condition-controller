//
// Created by arekc on 16/10/2022.
//

#ifndef INC_429TESTS_CGPIO_HPP
#define INC_429TESTS_CGPIO_HPP

#include <gpio.h>


class CGpio {
    GPIO_TypeDef * m_port;
    uint16_t  m_pin;

public:
  CGpio(GPIO_TypeDef *port, uint16_t pin);
    void toggle();
};


#endif//INC_429TESTS_CGPIO_HPP

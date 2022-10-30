//
// Created by arekc on 16/10/2022.
//

#include "../inc/Gpio.hpp"

Gpio::Gpio(GPIO_TypeDef *port, uint16_t pin)
  : m_port(port)
  , m_pin(pin)
{

}

void Gpio::toggle() {
  HAL_GPIO_TogglePin(m_port, m_pin);
}
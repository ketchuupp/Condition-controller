//
// Created by arekc on 16/10/2022.
//

#include "CGpio.hpp"

CGpio::CGpio(GPIO_TypeDef *port, uint16_t pin)
  : m_port(port)
  , m_pin(pin)
{

}

void CGpio::toggle() {
  HAL_GPIO_TogglePin(m_port, m_pin);
}
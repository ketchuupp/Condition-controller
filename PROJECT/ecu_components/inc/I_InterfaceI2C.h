//
// Created by arekc on 16/12/2022.
//

#ifndef INC_429TESTS_I_INTERFACEI2C_H
#define INC_429TESTS_I_INTERFACEI2C_H

#include <optional>
#include <vector>
#include <cstdint>

class I_InterfaceI2C {
public:
  I_InterfaceI2C() = default;

  virtual ~I_InterfaceI2C() = default;

  [[nodiscard]] virtual std::optional<std::vector<uint8_t>>
  read(uint8_t deviceAddress, int reg, uint8_t memoryAddressSize, int size) = 0;

  [[nodiscard]] virtual bool
  write(uint8_t deviceAddress, uint8_t reg, int memoryAddressSize, const std::vector<uint8_t> &data) = 0;

};


#endif //INC_429TESTS_I_INTERFACEI2C_H

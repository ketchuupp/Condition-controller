//
// Created by arekc on 16/12/2022.
//

#ifndef INC_429TESTS_COMMUNICATIONI2C_H
#define INC_429TESTS_COMMUNICATIONI2C_H

#include <main.h>
#include <optional>
#include <vector>
#include <I_InterfaceI2C.h>
#include <cmsis_os.h>


class CommunicationI2C : public I_InterfaceI2C {
  I2C_HandleTypeDef *m_i2cHandler;
  osMutexId osMutexI2cHandle;
  osMutexDef(osMutexI2c);

public:
  explicit CommunicationI2C(I2C_HandleTypeDef *i2cHandler);

  [[nodiscard]] std::optional<std::vector<uint8_t>>
  read(uint8_t deviceAddress, int memoryAddressSize, uint8_t reg, int size) override;

  [[nodiscard]] bool
  write(uint8_t deviceAddress, uint8_t reg, int memoryAddressSize, const std::vector<uint8_t> &data) override;

private:

};


#endif //INC_429TESTS_COMMUNICATIONI2C_H

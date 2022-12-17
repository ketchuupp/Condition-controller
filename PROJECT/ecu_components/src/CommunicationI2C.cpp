//
// Created by arekc on 16/12/2022.
//

#include "CommunicationI2C.h"

CommunicationI2C::CommunicationI2C(I2C_HandleTypeDef *i2cHandler) : m_i2cHandler(i2cHandler) {
  osMutexI2cHandle = osMutexCreate(osMutex(osMutexI2c));
}

std::optional<std::vector<uint8_t>>
CommunicationI2C::read(uint8_t deviceAddress, int reg, uint8_t memoryAddressSize, int size) {
  uint8_t data[size];

  osMutexWait(osMutexI2cHandle, HAL_MAX_DELAY);
  auto status = HAL_I2C_Mem_Read(m_i2cHandler, deviceAddress, reg,
                                 memoryAddressSize, data, size, HAL_MAX_DELAY);
  osMutexRelease(osMutexI2cHandle);

  if (status != HAL_OK)
    return {};

  std::vector<uint8_t> values;
  for (auto val: data)
    values.push_back(val);

  return values;
}

bool
CommunicationI2C::write(uint8_t deviceAddress, uint8_t reg, int memoryAddressSize,
                        const std::vector<uint8_t> &data) {
  uint8_t dataToSend[data.size()];

  for (size_t i = 0; i < data.size(); i++)
    dataToSend[i] = data.at(i);

  osMutexWait(osMutexI2cHandle, HAL_MAX_DELAY);
  auto status = HAL_I2C_Mem_Write(m_i2cHandler, deviceAddress, reg,
                                  memoryAddressSize, dataToSend, data.size(), HAL_MAX_DELAY);
  osMutexRelease(osMutexI2cHandle);

  if (status != HAL_OK)
    return false;

  return true;
}


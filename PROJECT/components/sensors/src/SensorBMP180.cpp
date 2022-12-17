//
// Created by arekc on 16/12/2022.
//

#include "SensorBMP180.h"
#include <cmath>
#include <debug.hpp>


SensorBMP180::SensorBMP180(I_InterfaceI2C *i2cHandler) : m_i2cHandler(i2cHandler) {
  read_calliberation_data();
}

bool SensorBMP180::readSensor() {
  BMP180_GetPress(3);
  return BMP180_GetTemp();
}

bool SensorBMP180::read_calliberation_data() {
  uint16_t Callib_Start = 0xAA;

  auto result = m_i2cHandler->read(devAddress, Callib_Start, 1, 22);

  if (!result.has_value())
    return false;

  auto getData = [&result](int index1, int index2) -> short {
    return result->at(index1) << 8 | result->at(index2);
  };

  AC1 = getData(0, 1);
  AC2 = getData(2, 3);
  AC3 = getData(4, 5);
  AC4 = getData(6, 7);
  AC5 = getData(8, 9);
  AC6 = getData(10, 11);
  B1 = getData(12, 13);
  B2 = getData(14, 15);
  MB = getData(16, 17);
  MC = getData(18, 19);
  MD = getData(20, 21);

  return true;
}

// Get uncompensated Temp
uint16_t SensorBMP180::Get_UTemp() {
  uint8_t Temp_RAW[2] = {0};
  std::vector<uint8_t> v{0x2e};
  auto write_result = m_i2cHandler->write(devAddress, 0xf4, 1, v);
  if (!write_result) {
    /* break fnc TODO */
    TRACE("I2c write temperature failed");
  }


  HAL_Delay(5);  // wait 4.5 ms

  auto read_result = m_i2cHandler->read(devAddress, 0xf6, 1, 2);
  if (!read_result.has_value()) {
    /* break fnc TODO */
    TRACE("I2c read temperature failed");
  }


  return ((read_result->at(0) << 8) + read_result->at(1));
}

bool SensorBMP180::BMP180_GetTemp(void) {
  UT = Get_UTemp();
  float X1 = (UT - AC6) * (AC5 / (pow(2, 15)));
  float X2 = (MC * (pow(2, 11))) / (X1 + MD);
  float B5 = X1 + X2;
  mTemperature = ((B5 + 8) / (pow(2, 4))) / 10;

  return true;
}

// Get uncompensated Pressure
uint32_t SensorBMP180::Get_UPress(int oss)   // oversampling setting 0,1,2,3
{
  uint8_t Press_RAW[3] = {0};

  std::vector<uint8_t> v{static_cast<uint8_t >(0x34 + (oss << 6))};
  auto write_result = m_i2cHandler->write(devAddress, 0xf4, 1, v);
  if (!write_result) {
    /* break fnc TODO */
    TRACE("I2c write temperature failed");
  }

  switch (oss) {
    case (0):
      HAL_Delay(5);
      break;
    case (1):
      HAL_Delay(8);
      break;
    case (2):
      HAL_Delay(14);
      break;
    case (3):
      HAL_Delay(26);
      break;
    default:
    TRACE("Unknown parameter");
  }
  auto read_result = m_i2cHandler->read(devAddress, 0xf6, 1, 3);
  if (!read_result.has_value()) {
    /* break fnc TODO */
    TRACE("I2c read temperature failed");
  }
  return (((read_result->at(0) << 16) + (read_result->at(1) << 8) + read_result->at(2)) >> (8 - oss));
}


float SensorBMP180::BMP180_GetPress(int oss) {
  UP = Get_UPress(oss);
  X1 = ((UT - AC6) * (AC5 / (pow(2, 15))));
  X2 = ((MC * (pow(2, 11))) / (X1 + MD));
  B5 = X1 + X2;
  B6 = B5 - 4000;
  X1 = (B2 * (B6 * B6 / (pow(2, 12)))) / (pow(2, 11));
  X2 = AC2 * B6 / (pow(2, 11));
  X3 = X1 + X2;
  B3 = (((AC1 * 4 + X3) << oss) + 2) / 4;
  X1 = AC3 * B6 / pow(2, 13);
  X2 = (B1 * (B6 * B6 / (pow(2, 12)))) / (pow(2, 16));
  X3 = ((X1 + X2) + 2) / pow(2, 2);
  B4 = AC4 * (unsigned long) (X3 + 32768) / (pow(2, 15));
  B7 = ((unsigned long) UP - B3) * (50000 >> oss);
  if (B7 < 0x80000000) Press = (B7 * 2) / B4;
  else Press = (B7 / B4) * 2;
  X1 = (Press / (pow(2, 8))) * (Press / (pow(2, 8)));
  X1 = (X1 * 3038) / (pow(2, 16));
  X2 = (-7357 * Press) / (pow(2, 16));
  Press = Press + (X1 + X2 + 3791) / (pow(2, 4));
  mPressure = Press / 100;
  return Press;
}


float SensorBMP180::BMP180_GetAlt(int oss) {
  BMP180_GetPress(oss);
  return 44330.f * (1 - (pow((Press / (float) atmPress), 0.19029495718)));
}

float SensorBMP180::getPressure() const {
  return mPressure;
}

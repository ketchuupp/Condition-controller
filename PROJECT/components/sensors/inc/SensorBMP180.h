//
// Created by arekc on 16/12/2022.
//

#ifndef INC_429TESTS_SENSORBMP180_H
#define INC_429TESTS_SENSORBMP180_H

#include <IConditionSensor.h>
#include <main.h>
#include <I_InterfaceI2C.h>


class SensorBMP180
        :
                public IConditionSensor {
  I_InterfaceI2C *m_i2cHandler;
  const uint8_t devAddress{0xee};
  const unsigned atmPress{101325};
  float mPressure{};

public:
  explicit SensorBMP180(I_InterfaceI2C *i2cHandler);

  bool readSensor() override;

  float getPressure() const;

private:
  // Defines according to the datsheet
  short AC1 = 0;
  short AC2 = 0;
  short AC3 = 0;
  unsigned short AC4 = 0;
  unsigned short AC5 = 0;
  unsigned short AC6 = 0;
  short B1 = 0;
  short B2 = 0;
  short MB = 0;
  short MC = 0;
  short MD = 0;

/********************/
  long UT = 0;
  long UP = 0;
  long X1 = 0;
  long X2 = 0;
  long X3 = 0;
  long B3 = 0;
  long B5 = 0;
  unsigned long B4 = 0;
  long B6 = 0;
  unsigned long B7 = 0;

/*******************/
  long Press = 0;
  long Temp = 0;

  bool read_calliberation_data();

  // Get uncompensated Temp
  uint16_t Get_UTemp();

  bool BMP180_GetTemp();

  uint32_t Get_UPress(int oss);   // oversampling setting 0,1,2,3

  float BMP180_GetPress(int oss);

  float BMP180_GetAlt(int oss);
};


#endif //INC_429TESTS_SENSORBMP180_H

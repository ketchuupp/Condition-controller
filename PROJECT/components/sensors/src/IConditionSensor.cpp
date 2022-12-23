//
// Created by arekc on 18/10/2022.
//

#include "IConditionSensor.h"



float IConditionSensor::getHumidity() const {
  return mHumidity;
}

float IConditionSensor::getTemperature() const {
  return mTemperature;
}

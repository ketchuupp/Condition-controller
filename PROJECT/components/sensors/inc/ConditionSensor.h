//
// Created by arekc on 18/10/2022.
//

#ifndef INC_429TESTS_CONDITIONSENSOR_H
#define INC_429TESTS_CONDITIONSENSOR_H


class ConditionSensor {
public:
  ConditionSensor() = default;

  ~ConditionSensor() = default;

  float getHumidity();

  float getTemperature();

  virtual bool readSensor() = 0;

public:
  float mTemperature;
  float mHumidity;
};


#endif//INC_429TESTS_CONDITIONSENSOR_H

//
// Created by arekc on 18/10/2022.
//

#ifndef INC_429TESTS_ICONDITIONSENSOR_H
#define INC_429TESTS_ICONDITIONSENSOR_H


class IConditionSensor {
public:
  IConditionSensor() = default;

  ~IConditionSensor() = default;

  [[nodiscard]] float getHumidity() const;

  [[nodiscard]] float getTemperature() const;

  // pure function
  virtual bool readSensor() = 0;

public:
  float mTemperature{};
  float mHumidity{};
};


#endif//INC_429TESTS_ICONDITIONSENSOR_H

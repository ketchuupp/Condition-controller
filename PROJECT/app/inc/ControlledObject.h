//
// Created by arekc on 30/10/2022.
//

#ifndef INC_429TESTS_CONTROLLEDOBJECT_H
#define INC_429TESTS_CONTROLLEDOBJECT_H

#include "ConditionSensor.h"
#include <OutputDeviceController.h>
#include <list>
#include <string>
#include <time.h>
#include <vector>

class ControlledObject {
public:
  enum controlled_by {
    NONE,
    HUMIDITY,
    TEMPERATURE,
    DAILY_MODE
  };

  /**
     * ON for temperature:
     *  power device on if temperature is bellow required, power off otherwise
     * ON for humidity:
     *  power device on if humidity is bellow required, power off otherwise
     * ON for daily mode:
     *  power device on if is day, power off otherwise
     * OFF is opposite to ON
     */
  enum state_device {
    ON,
    OFF
  };

  ControlledObject() = delete;

  ControlledObject(std::string name, ConditionSensor *sensor);

  bool setTemperature(float temp);

  bool setHumidity(float humid);

  bool setHumidityDeviation(float devHumid);

  bool setTemperatureDeviation(float devTemp);

  bool setDayTime(struct tm startDay, struct tm endDay);

  int addControlledDevice(std::string name, OutputDeviceController *dev, controlled_by ctr, state_device state);

  void doAllOperations();

  bool isDay();

  void setMName(const std::string &mName);

  const std::string &getMName() const;

private:
  struct output_device {
    int id;
    std::string mName;
    controlled_by mCtrl;
    state_device mSetStateByUser;
    state_device mCurrentDeviceState;
    OutputDeviceController *mDevice;
  };

  std::string mName;
  ConditionSensor *mSensor;

  float mTemperature;
  float mRequiredTemperature;
  float mMaxTemperatureDeviation;

  float mHumidity;
  float mRequiredHumidity;
  float mMaxHumidityDeviation;

  struct tm mStartDay;
  struct tm mEndDay;
  bool mDailyMode;

  std::vector<output_device *> mDeviceVector;
};


#endif//INC_429TESTS_CONTROLLEDOBJECT_H

//
// Created by arekc on 30/10/2022.
//

#ifndef INC_429TESTS_CONTROLLEDOBJECT_H
#define INC_429TESTS_CONTROLLEDOBJECT_H

#include "IConditionSensor.h"
#include <IOutputDeviceController.h>
#include <list>
#include <string>
#include <ctime>
#include <vector>

class ControlledObject {
private:
  bool isDay();

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
     * OFF is in opposite to ON
     */
  enum state_device {
    ON,
    OFF
  };

  ControlledObject() = delete;

  ControlledObject(std::string name, IConditionSensor *sensor);

  bool setTemperature(float temp);

  bool setHumidity(float humid);

  bool setHumidityDeviation(float devHumid);

  bool setTemperatureDeviation(float devTemp);

  bool setDayTime(struct tm startDay, struct tm endDay);

  unsigned int addControlledDevice(std::string name, IOutputDeviceController *dev, controlled_by ctr, state_device state);

  void doAllOperations();

  void setMName(const std::string &mName);

  [[nodiscard]] const std::string &getMName() const;

private:
  struct output_device {
    unsigned id;
    std::string mName;
    controlled_by mCtrl;
    state_device mSetStateByUser;
    state_device mCurrentDeviceState;
    IOutputDeviceController *mDevice;
  };

  std::string mName;
  IConditionSensor *mSensor;

  float mTemperature{};
  float mRequiredTemperature{};
  float mMaxTemperatureDeviation{};

  float mHumidity{};
  float mRequiredHumidity{};
  float mMaxHumidityDeviation{};

  struct tm mStartDay{};
  struct tm mEndDay{};
  bool mDailyMode{};

  std::vector<output_device *> mDeviceVector;
};


#endif//INC_429TESTS_CONTROLLEDOBJECT_H

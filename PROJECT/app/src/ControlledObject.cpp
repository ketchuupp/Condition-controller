//
// Created by arekc on 30/10/2022.
//

#include "ControlledObject.h"

#include <utility>
#include <debug.hpp>
#include <task.h>

TRACE_INIT(ControlledObject.cpp)

#define MAX_TEMPERATURE 50.f
#define MIN_TEMPERATURE 0.f
#define MAX_HUMIDITY 100.f
#define MIN_HUMIDITY 0.f

ControlledObject::ControlledObject(std::string name, IConditionSensor *sensor)
    : mName(name), mSensor(sensor) {
  mDeviceVector.reserve(3);
  TRACE_ARG("Controlled object %s created", name.c_str());
}

bool ControlledObject::setTemperature(float temp) {
  if (temp > MAX_TEMPERATURE) {
    TRACE_ARG("%.1f is unsupported. Max value is %f", temp, MAX_TEMPERATURE);
    return false;
  }
  if (temp < MIN_TEMPERATURE) {
    TRACE_ARG("%.1f is unsupported. Max value is %f", temp, MAX_TEMPERATURE);
    return false;
  }

  mRequiredTemperature = temp;
  return true;
}

bool ControlledObject::setHumidity(float humid) {

  if (humid > MAX_HUMIDITY) {
    TRACE_ARG("%.1f is unsupported. Max value is %f", humid, MAX_HUMIDITY);
    return false;
  }

  if (humid < MIN_HUMIDITY) {
    TRACE_ARG("%.1f is unsupported. Min value is %f", humid, MIN_HUMIDITY);
    return false;
  }

  mRequiredHumidity = humid;
  return true;
}

bool ControlledObject::setHumidityDeviation(float devHumid) {
  if (devHumid > MAX_HUMIDITY) {
    TRACE_ARG("%.1f is unsupported. Max value is %f", devHumid, MAX_HUMIDITY);
    return false;
  }

  if (devHumid < MIN_HUMIDITY) {
    TRACE_ARG("%.1f is unsupported. Min value is %f", devHumid, MIN_HUMIDITY);
    return false;
  }

  mMaxHumidityDeviation = devHumid;
  return true;
}

bool ControlledObject::setTemperatureDeviation(float devTemp) {
  if (devTemp > MAX_TEMPERATURE) {
    TRACE_ARG("%.1f is unsupported. Max value is %f", devTemp, MAX_TEMPERATURE);
    return false;
  }
  if (devTemp < MIN_TEMPERATURE) {
    TRACE_ARG("%.1f is unsupported. Max value is %f", devTemp, MAX_TEMPERATURE);
    return false;
  }

  mRequiredTemperature = devTemp;
  return true;
}

bool ControlledObject::setDayTime(struct tm startDay, struct tm endDay) {
  mStartDay = startDay;
  mEndDay = endDay;

  return true;
}

unsigned int ControlledObject::addControlledDevice(std::string name, IOutputDeviceController *dev,
                                                   ControlledObject::controlled_by ctr,
                                                   ControlledObject::state_device state) {
  constexpr int return_error = -1;

  if (dev == nullptr) {
    TRACE("Output device pointer is nullptr.");
    return return_error;
  }

  auto id = mDeviceVector.size() + 1;
  mDeviceVector.push_back(new output_device{id, std::move(name), ctr, state, OFF, dev});
  if (mDeviceVector.back() == nullptr)
  {
    TRACE("Cannot create output device controller");
    return return_error;
  }

  return id;
}

void ControlledObject::doAllOperations() {
  mSensor->readSensor();
  mTemperature = mSensor->getTemperature();
  mHumidity = mSensor->getHumidity();
//  TRACE_ARG("Temperature: %f", mTemperature);


  for (auto dev: mDeviceVector) {
    switch (dev->mCtrl) {
      case NONE:
        if (dev->mSetStateByUser == ON)
          dev->mDevice->turnOn();
        else
          dev->mDevice->turnOff();
        break;

      case TEMPERATURE:
        if (mTemperature - mMaxTemperatureDeviation < mRequiredTemperature)
          dev->mSetStateByUser == ON ? dev->mDevice->turnOn() : dev->mDevice->turnOff();
        else if (mTemperature + mMaxTemperatureDeviation > mRequiredTemperature)
          dev->mSetStateByUser == ON ? dev->mDevice->turnOff() : dev->mDevice->turnOn();
        break;

      case HUMIDITY:
        if (mHumidity - mMaxHumidityDeviation < mRequiredHumidity)
          dev->mSetStateByUser == ON ? dev->mDevice->turnOn() : dev->mDevice->turnOff();
        else if (mHumidity + mMaxHumidityDeviation > mRequiredHumidity)
          dev->mSetStateByUser == ON ? dev->mDevice->turnOff() : dev->mDevice->turnOn();
        break;

      case DAILY_MODE:
        if (isDay())
          dev->mSetStateByUser == ON ? dev->mDevice->turnOn() : dev->mDevice->turnOff();
        else
          dev->mSetStateByUser == ON ? dev->mDevice->turnOff() : dev->mDevice->turnOn();
        break;

      default:
        break;
    }// switch
  }  // for loop
}

bool ControlledObject::isDay() {
  // TODO
  return true;
}

void ControlledObject::setMName(const std::string &mName) {
  ControlledObject::mName = mName;
}

const std::string &ControlledObject::getMName() const {
  return mName;
}

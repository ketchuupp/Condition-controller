//
// Created by arekc on 15/10/2022.
//

#include <App.h>
#include <debug.hpp>
#include <CUartDriver.h>
#include <SensorBMP180.h>
#include <CommunicationI2C.h>
#include <i2c.h>
#include <QueueAppServer.h>
#include <Cwrappers.h>
#include <UartServer.h>

App::App() {
  I_InterfaceI2C *bmpI2c = new CommunicationI2C(&hi2c3);
  IConditionSensor * sensor = new SensorBMP180(bmpI2c);
  mMainController.createControlledObject("Object 1", sensor);
}

[[noreturn]] void App::run() {
  TRACE("APP MAIN THREAD START");
  osDelay(100);

  for (;;) {

    mGreenLed.toggle();
    mMainController.updateControlledObjectsStates();
    std::string mess = "KKKSSSHD78654UJ5";
    pushMessToQueue(mess);
    osDelay(500);
  }
}

App::~App() {

}

bool App::pushMessToQueue(std::string &mess) {
  char *str = new char[100];
  strcpy(str, mess.c_str());
  if (!xQueueSend(*m_queueAppToUartServer,
          str, portMAX_DELAY) == pdPASS)
  {
    TRACE("Queue cannot send message!");
  }
  return true;
}


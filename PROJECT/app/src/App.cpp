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

TRACE_INIT

App::App() {

}

[[noreturn]] void App::run() {
  TRACE("APP MAIN THREAD START");
  osDelay(100);
  int iter = 0;

    I_InterfaceI2C *bmpI2c = new CommunicationI2C(&hi2c3);
  IConditionSensor *sensor = new SensorBMP180(bmpI2c);

  for (;;) {
    getMessFromQueue();
    if (!m_queueMessFromTasks.empty()) {
//      TRACE_ARG("Received message: %s", queueMessFromTasks.front().c_str());
      std::string mess(std::move(m_queueMessFromTasks.front()));
      m_queueMessFromTasks.pop();
      if (mess == "create")
      {
//        mMainController.createControlledObject("Object 1", sensor);
      }
      else if (mess == "read_temp")
      {
        sensor->readSensor();
        auto temp = sensor->getTemperature();
        TRACE_ARG("Temperature: %f", temp);
      }
      else
      {
        TRACE_ARG("Unknown command \"%s\"", mess.c_str());
        std::string messToSend = "Unknown command \"" + mess + "\"";
        sendMessageToServer(messToSend);
      }

    }
    m_GreenLed.toggle();
//    mMainController.updateControlledObjectsStates();

    osDelay(100);
    iter++;
  }
}

App::~App() {

}

void App::addSendingQueueToServer(TaskQueue<char, 10, 100> *sendingQueue) {
  if (sendingQueue == nullptr) {
    TRACE("Incoming parameter pass to nullptr");
    return;
  }

  m_sendingQueueToServer = sendingQueue;
}

bool App::sendMessageToServer(const std::string &mess) {
  std::string toSend = name + ' ' + mess;
  auto status = m_sendingQueueToServer->pushMessage(toSend.c_str());
  if (status)
    return true;

  return false;
}

void App::addReceiveQueue(TaskQueue<char, 10, 100> *receiveQueue) {
  if (receiveQueue == nullptr) {
    TRACE("Incoming parameter pass to nullptr");
    return;
  }

  m_receivingQueueChar = receiveQueue;
}

bool App::getMessFromQueue() {
  auto result = m_receivingQueueChar->popMessage();
  if (!result.has_value())
    return false;

  m_queueMessFromTasks.push(result.value());
  return true;
}


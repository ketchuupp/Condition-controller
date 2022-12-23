//
// Created by arekc on 17/12/2022.
//

#include "QueueAppServer.h"
//class QueueAppServer {
//static std::queue<std::string> queueMess;
xQueueHandle messQueue;

TRACE_INIT(QueueAppServer.cpp)

//public:
void QueueAppServer()
{
  messQueue = xQueueCreate(10, 100*sizeof(char));
  if (messQueue == 0)
  TRACE("Cannot create queue");
}

void addMessage(std::string mess) {
  char *ch = new char[100];
  strcpy(ch, mess.c_str());
  if (xQueueSend(messQueue, ch, portMAX_DELAY) == pdPASS)
  {
    TRACE("Queue send succesfull");
  }
}

std::optional<std::string> popMessage() {
  char str[100];
  if (xQueueReceive(messQueue, str, portMAX_DELAY) == pdPASS)
    return str;

  return {};
}
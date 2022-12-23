//
// Created by arekc on 23/12/2022.
//

#include "ThreadClass.h"
#include "debug.hpp"

TRACE_INIT

void ThreadClass::addReceiveQueue(TaskQueue<char, 10, 100> *receiveQueue) {
  if (receiveQueue == nullptr) {
    TRACE("Incoming parameter pass to nullptr");
    return;
  }

  m_receivingQueueChar = receiveQueue;
}

bool ThreadClass::getMessFromQueue() {
  auto result = m_receivingQueueChar->popMessage();
  if (!result.has_value())
    return false;

  m_queueMessFromTasks.push(result.value());
  return true;
}
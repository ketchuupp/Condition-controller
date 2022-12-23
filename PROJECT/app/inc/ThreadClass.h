//
// Created by arekc on 23/12/2022.
//

#ifndef INC_429TESTS_THREADCLASS_H
#define INC_429TESTS_THREADCLASS_H

#include "TaskQueue.hpp"
#include <queue>

class ThreadClass {
public:
  ThreadClass() = default;

  virtual ~ThreadClass() = default;

  virtual void run() {}

  void addReceiveQueue(TaskQueue<char, 10, 100> *receivingQueue);

protected:
  bool getMessFromQueue();

  std::string m_name{};
  TaskQueue<char, 10, 100> *m_receivingQueueChar{};
  std::queue<std::string> m_queueMessFromTasks;

private:

};


#endif //INC_429TESTS_THREADCLASS_H

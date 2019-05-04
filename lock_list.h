//
// Copyright 2018 CStanKonrad
//

#ifndef SRC_LOCK_LIST_H_
#define SRC_LOCK_LIST_H_

#include <condition_variable>

class LockList {
 public:
  LockList() = default;
  LockList(const LockList &b) = delete;

  void lock(std::unique_lock<std::mutex> &lock);

  void unlock(std::unique_lock<std::mutex> &lock);

  void setNext(LockList *next);

  LockList *getNext();

 private:
  std::condition_variable cv;
  std::mutex sleepMutex;
  bool open = false;

  LockList *nextLock = nullptr;
};

#endif  // SRC_LOCK_LIST_H_

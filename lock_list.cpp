//
// Copyright 2018 CStanKonrad
//

#include "lock_list.h"

void LockList::lock(std::unique_lock<std::mutex> &lock) {
  lock.unlock();
  std::unique_lock<std::mutex> sleepLock(this->sleepMutex);
  while (!this->open) {
    this->cv.wait(sleepLock);
  }
  this->open = false;
  lock.lock();
}

void LockList::unlock(std::unique_lock<std::mutex> &lock) {
  this->sleepMutex.lock();
  open = true;
  this->sleepMutex.unlock();
  cv.notify_one();
  lock.unlock();
}

void LockList::setNext(LockList *next) { this->nextLock = next; }

LockList *LockList::getNext() { return this->nextLock; }

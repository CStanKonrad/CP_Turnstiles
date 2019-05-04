//
// Copyright 2018 CStanKonrad
//

#include "turnstile.h"
#include <mutex>
#include "turnstile_pool.h"

static TurnstilePool &getTurnstilePool() {
  static TurnstilePool pool;
  return pool;
}

void Mutex::lock() {
  LockList *tmpLock = getTurnstilePool().getTmpLock();

  std::unique_lock<std::mutex> lock(*getTurnstilePool().getGlobalLock(this));

  if (this->turnstile == nullptr) {
    this->turnstile = tmpLock;
  } else {
    LockList *threadLock = getTurnstilePool().getThreadLock().release();
    threadLock->setNext(nullptr);

    if (this->turnstile == tmpLock) {
      this->turnstile = threadLock;
    } else {
      threadLock->setNext(this->turnstile->getNext());
      this->turnstile->setNext(threadLock);
    }

    this->turnstile->lock(lock);

    threadLock = this->turnstile->getNext();

    if (threadLock == nullptr) {
      threadLock = this->turnstile;
      this->turnstile = tmpLock;
    } else {
      this->turnstile->setNext(threadLock->getNext());
    }

    lock.unlock();
    getTurnstilePool().getThreadLock().reset(threadLock);
  }
}

void Mutex::unlock() {
  LockList *tmpLock = getTurnstilePool().getTmpLock();
  std::unique_lock<std::mutex> lock(*getTurnstilePool().getGlobalLock(this));

  if (this->turnstile == tmpLock) {
    this->turnstile = nullptr;
  } else {
    this->turnstile->unlock(lock);
  }
}

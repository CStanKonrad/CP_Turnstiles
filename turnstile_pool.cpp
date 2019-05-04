//
// Copyright 2018 CStanKonrad
//

#include "turnstile_pool.h"

std::mutex* TurnstilePool::getGlobalLock(Mutex* acquirer) {
  return &this->globalLocks[hash(acquirer)];
}

LockList* TurnstilePool::getTmpLock() { return &this->tmpLock; }

std::unique_ptr<LockList>& TurnstilePool::getThreadLock() {
  thread_local std::unique_ptr<LockList> lock(new LockList());

  return lock;
}

size_t TurnstilePool::hash(Mutex* ptr) {
  return (reinterpret_cast<size_t>(ptr) >> static_cast<size_t>(3)) %
         TurnstilePool::GLOBAL_LOCKS;
}

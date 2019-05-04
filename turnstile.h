//
// Copyright 2018 CStanKonrad
//

#ifndef SRC_TURNSTILE_H_
#define SRC_TURNSTILE_H_

#include "lock_list.h"

class Mutex {
 public:
  Mutex() = default;

  Mutex(const Mutex &) = delete;

  void lock();    // NOLINT
  void unlock();  // NOLINT

 private:
  LockList *turnstile = nullptr;
};

#endif  // SRC_TURNSTILE_H_

//
// Copyright 2018 CStanKonrad
//

#ifndef SRC_TURNSTILE_POOL_H_
#define SRC_TURNSTILE_POOL_H_

#include <mutex>
#include "lock_list.h"
#include "turnstile.h"

class TurnstilePool {
 public:
  TurnstilePool() = default;

  std::mutex* getGlobalLock(Mutex* acquirer);

  LockList* getTmpLock();

  std::unique_ptr<LockList>& getThreadLock();

 private:
  size_t hash(Mutex* ptr);

  LockList tmpLock;
  static constexpr size_t GLOBAL_LOCKS = 257;
  std::mutex globalLocks[GLOBAL_LOCKS];
};

#endif  // SRC_TURNSTILE_POOL_H_

//
// Created by creeper on 10/10/24.
//

#ifndef MINILOG_INCLUDE_MINILOG_SPIN_MUTEX_H
#define MINILOG_INCLUDE_MINILOG_SPIN_MUTEX_H
#include <atomic>
namespace minilog {
struct spin_mutex {
  void lock() {
    while (flag.test_and_set(std::memory_order_acquire));
  }
  void unlock() {
    flag.clear(std::memory_order_release);
  }
  std::atomic_flag flag = ATOMIC_FLAG_INIT;
};
}
#endif //MINILOG_INCLUDE_MINILOG_SPIN_MUTEX_H

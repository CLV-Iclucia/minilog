//
// Created by creeper on 10/10/24.
//
#include <minilog/logger.h>

int main() {
  minilog::info("Hello, World!");
  minilog::info("Test format {}", 42);
  minilog::warn("Test format {}", 42);
  auto logger = minilog::createFileLogger("test.txt");
  logger->info("Hello, World!");
  logger->info("Test format {}", 42);
  logger->warn("Test format {}", 42);
  return 0;
}
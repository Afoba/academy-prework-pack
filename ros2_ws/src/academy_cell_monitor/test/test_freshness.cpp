#include <chrono>
#include <iostream>
#include <optional>

#include "academy_cell_monitor/freshness.hpp"

int main() {
  using academy_cell_monitor::SteadyTime;
  using academy_cell_monitor::is_stale;
  using namespace std::chrono_literals;

  const SteadyTime now{10s};
  const auto timeout = 500ms;

  if (!is_stale(now, std::nullopt, timeout)) {
    std::cerr << "No message must be stale.\n";
    return 1;
  }
  if (is_stale(now, now - 200ms, timeout)) {
    std::cerr << "A state received 200 ms ago must be fresh.\n";
    return 1;
  }
  if (!is_stale(now, now - 700ms, timeout)) {
    std::cerr << "A state received 700 ms ago must be stale.\n";
    return 1;
  }
  std::cout << "All freshness cases passed.\n";
  return 0;
}

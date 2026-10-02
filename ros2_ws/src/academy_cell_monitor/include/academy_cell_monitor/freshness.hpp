#pragma once

#include <chrono>
#include <optional>

namespace academy_cell_monitor {

using SteadyTime = std::chrono::steady_clock::time_point;

// Prework TODO: return true if no state has arrived or if its age exceeds timeout.
// This checks local arrival freshness, not the JointState header timestamp.
inline bool is_stale(
    SteadyTime now,
    std::optional<SteadyTime> last_received,
    std::chrono::milliseconds timeout) {
  (void)now;
  (void)last_received;
  (void)timeout;
  return true;
}

}  // namespace academy_cell_monitor

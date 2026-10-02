#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/bool.hpp"

#include "academy_cell_monitor/freshness.hpp"

namespace academy_cell_monitor {

class CellMonitor : public rclcpp::Node {
 public:
  CellMonitor() : Node("cell_monitor") {
    state_subscription_ = create_subscription<sensor_msgs::msg::JointState>(
        "/follower/joint_states", 10,
        std::bind(&CellMonitor::on_state, this, std::placeholders::_1));
    freshness_publisher_ = create_publisher<std_msgs::msg::Bool>(
        "/cell/state_fresh", 10);
    timer_ = create_wall_timer(
        std::chrono::milliseconds(100),
        std::bind(&CellMonitor::on_timer, this));
  }

 private:
  void on_state(const sensor_msgs::msg::JointState::SharedPtr message) {
    (void)message;
    // Prework TODO: under state_mutex_, record this message's local arrival
    // time in last_received_. Do not use the illustrative header timestamp.
  }

  void on_timer() {
    std::optional<SteadyTime> last_received;
    {
      std::lock_guard<std::mutex> lock(state_mutex_);
      last_received = last_received_;
    }

    constexpr auto timeout = std::chrono::milliseconds(500);
    const bool fresh = !is_stale(
        std::chrono::steady_clock::now(), last_received, timeout);
    std_msgs::msg::Bool status;
    status.data = fresh;
    freshness_publisher_->publish(status);

    if (!last_published_.has_value() || *last_published_ != fresh) {
      RCLCPP_INFO(get_logger(), "state_fresh=%s", fresh ? "true" : "false");
      last_published_ = fresh;
    }
  }

  std::mutex state_mutex_;
  std::optional<SteadyTime> last_received_;
  std::optional<bool> last_published_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr state_subscription_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr freshness_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace academy_cell_monitor

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<academy_cell_monitor::CellMonitor>());
  rclcpp::shutdown();
  return 0;
}

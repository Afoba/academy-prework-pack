# Synthetic cell monitor - C++ / ROS 2 Humble prework

This starter is part of the Academy prework. It reads synthetic follower joint
states and publishes a diagnostic Boolean on `/cell/state_fresh`. It does not
send commands or connect to a physical robot. The 500 ms timeout is illustrative,
not a robot safety limit. The ROS graph in `ros2-graph-case.txt` is an invented
reading exercise, not a set of running nodes. The only live input in this
exercise is the `ros2 topic pub` command below; it generates example
`JointState` messages in the local container. No recording, simulator or
physical arm is needed.

## What you implement

Complete `is_stale()` in `include/academy_cell_monitor/freshness.hpp`:

- No joint-state message received yet: stale.
- Last message received less than or exactly 500 ms ago: fresh.
- Last message received more than 500 ms ago: stale.

Then complete `on_state()` in `src/cell_monitor.cpp`: when the ROS 2 subscription
receives a `JointState`, record the local `std::chrono::steady_clock::now()`
under the supplied mutex. The timer and diagnostic publisher are provided.
The test is **expected to fail** until you implement `is_stale()`, and the
runtime stays stale until you also complete the callback. This exercise checks
time since local arrival, not the `JointState.header.stamp`; source timestamps
and clock alignment are discussed in the Academy.

## Run in the supplied Humble environment

From the folder containing `compose.yaml`, run:

```bash
docker compose up -d
docker compose exec humble bash
```

Inside that container shell:

```bash
source /opt/ros/humble/setup.bash
cd /workspace/ros2_ws
colcon build --packages-select academy_cell_monitor
source install/setup.bash
colcon test --packages-select academy_cell_monitor
colcon test-result --verbose
ros2 run academy_cell_monitor cell_monitor
```

The container image may take time to download on the first run. If Docker is
unavailable, you can still edit the code and describe the setup problem in your
README; this prework is not an entry test. On a native Ubuntu 22.04 ROS 2 Humble
installation, run the same commands after sourcing `/opt/ros/humble/setup.bash`.
Docker stores build, install and log outputs in named volumes, not in the
unpacked folder; your source edits stay in the folder.

## Try a synthetic topic

Leave the node running. Open a second terminal on your computer and run
`docker compose exec humble bash` from the package ZIP's top-level folder.
Inside it, source both setup files as above and observe:

```bash
ros2 node list
ros2 topic list
ros2 topic echo /cell/state_fresh
```

Initially `data` should be `false`. In a third container terminal, source the
ROS setup and publish synthetic joint states:

```bash
ros2 topic pub -r 5 -t 20 /follower/joint_states sensor_msgs/msg/JointState "{name: ['joint1'], position: [0.0]}"
```

This ROS 2 CLI publisher invents one `joint1` position (`0.0`) five times per
second for 20 messages on `/follower/joint_states`, then stops automatically.
It is not reading a sensor. The message header stamp is left at zero; the node
checks local receipt time instead. While messages arrive, `data` should become
`true`; more than 500 ms after publication stops, it should return to `false`.
Do not publish to a physical robot's topics. This example remains inside one
local container.

When finished, leave each container shell and run `docker compose down` from
the top-level folder. The Docker container is removed; your source files remain.

## What to share

Include your changed `freshness.hpp` and `cell_monitor.cpp`, the test result or
a short account of a setup blocker, and a brief explanation of the subscriber,
publisher and stale transition in your personal practice repository. The
synthetic files and this starter should stay in a private repository unless
the Academy explicitly approves publication.

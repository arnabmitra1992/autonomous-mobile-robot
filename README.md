# autonomous-mobile-robot
# Autonomous Mobile Robot (AMR)

## Project Overview

An ongoing robotics engineering project focused on developing an autonomous mobile robot capable of environment exploration, mapping, localization, path planning and autonomous navigation.

The project follows a bottom-up development approach, starting with fundamental robotics algorithms implemented from scratch in C++, followed by integration with ROS2, Gazebo, SLAM, Nav2 and physical robotic hardware.

## Project Objectives

- Develop autonomous exploration and path-planning algorithms from scratch.
- Understand and implement robotic sensor processing.
- Integrate localization, mapping and navigation systems.
- Develop autonomous decision-making using Behavior Trees.
- Deploy and validate algorithms on physical robotic hardware.
- Implement robust software testing and debugging practices.

## Current Implementation

### Phase 1 — Standalone C++ Algorithms

- [x] Occupancy grid representation
- [x] Frontier detection
- [x] Breadth-First Search (BFS)
- [x] Reachability analysis
- [x] Shortest-path calculation
- [x] Dijkstra path planning
- [x] Frontier clustering
- [x] Centroid-based exploration goal selection
- [x] Reachable frontier selection
- [x] Simulated sensor observations
- [x] Dynamic occupancy grid updates
- [x] Autonomous exploration loop

### Autonomous Exploration Pipeline

```text
Initialize occupancy grid
          |
          v
Perform sensor observation
          |
          v
Detect frontiers
          |
          v
Cluster frontiers
          |
          v
Select reachable exploration goal
          |
          v
Generate path using Dijkstra
          |
          v
Simulate robot movement
          |
          v
Update occupancy grid
          |
          v
Repeat until no reachable exploration goals remain
```

## Initial Simulation Results

The autonomous exploration algorithm was tested in a 4 × 7 occupancy grid environment containing obstacles, a central wall and a connecting passage.

| Metric | Result |
|---|---:|
| Total grid cells | 28 |
| Discovered cells | 25 |
| Overall map coverage | 89.3% |
| Accessible free-space coverage | 100% |
| Incorrectly classified cells | 0 |
| Remaining frontiers | 0 |

The remaining unknown cells are obstacle cells that cannot be observed using the simplified four-neighbor sensor model.

## Development Roadmap

### Phase 2 — ROS2 and Sensor Integration

- [ ] LiDAR data processing
- [ ] Wheel odometry
- [ ] IMU integration
- [ ] ROS2 C++ publishers and subscribers
- [ ] TF2 coordinate transformations
- [ ] Sensor fusion using Extended Kalman Filter (EKF)

### Phase 3 — Localization, Mapping and Navigation

- [ ] Gazebo simulation
- [ ] SLAM Toolbox
- [ ] AMCL localization
- [ ] A* path planning
- [ ] Nav2 integration
- [ ] Autonomous frontier-based mapping
- [ ] Costmaps and obstacle avoidance

### Phase 4 — Autonomous Decision-Making

- [ ] BehaviorTree.CPP
- [ ] Groot2 visualization
- [ ] Autonomous mission execution
- [ ] Navigation recovery behaviors
- [ ] Automatic map saving and loading

### Phase 5 — Physical Robot Deployment

- [ ] NVIDIA Jetson Nano integration
- [ ] ESP32 motor control
- [ ] Wheel encoder integration
- [ ] Physical LiDAR integration
- [ ] Hardware and simulation validation

### Phase 6 — Software Quality and Reliability

- [ ] Unit and integration testing
- [ ] Fault injection and recovery testing
- [ ] Docker containerization
- [ ] CI/CD using GitHub Actions
- [ ] Performance benchmarking
- [ ] Technical documentation

## Technology Stack

| Category | Technologies |
|---|---|
| Programming | C++, Python |
| Robotics middleware | ROS2 Humble |
| Simulation | Gazebo |
| Path planning | BFS, Dijkstra, A* |
| Mapping and localization | SLAM Toolbox, AMCL |
| Navigation | Nav2 |
| Decision-making | BehaviorTree.CPP, Groot2 |
| Hardware | Jetson Nano, ESP32, LiDAR, IMU, wheel encoders |
| Development tools | Git, GitHub, VS Code, CMake, Docker |
| Operating system | Ubuntu 22.04 |

The technology stack includes both currently implemented and planned technologies.

## Project Status

**Under active development — Phase 1 completed for the initial test environment.**

This repository documents the incremental development of an autonomous mobile robot, from fundamental algorithms to a complete robotic software and hardware system.

## Author

Arnab Mitra

Mechanical Engineer | Robotics and Autonomous Systems

Interested in robotics software engineering, autonomous navigation, motion planning, industrial mobile robotics and simulation.
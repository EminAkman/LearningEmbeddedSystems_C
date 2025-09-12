# Modular Sensor Framework (OOP in C)

This project demonstrates how to implement **OOP concepts in C** (encapsulation, polymorphism, strategy, observer, state) by creating a **modular sensor framework**. It allows you to manage multiple sensor types through a common interface, apply filters, trigger threshold events, and handle state transitions.

---

## Features

- **Common Sensor Interface:** `init()`, `read()`, `calibrate()`, `destroy()`
- **Sensor Examples:** TempSensor, DistanceSensor (MesafeSens); easy to add more
- **SensorManager:** Manage, list, add, and remove sensors from a single point
- **Filter Strategy:** Moving Average, Median, or no filter (runtime configurable)
- **Observer Pattern:** Callback triggered when threshold values are exceeded
- **State Machine:** INIT → RUNNING → ERROR → SHUTDOWN
- **CLI Parameters:** e.g. `--rate 100ms --filter ma:5 --th 30.0 --add temp --list --log out.txt`
- **Logging:** Outputs to console and/or file

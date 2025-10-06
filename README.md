# 🖥️ Monitoring App

## 📘 Overview

**Monitoring App** is a desktop system monitor built with **C++** and **Dear ImGui**.  
It displays real-time system performance metrics — including **CPU**, **RAM**, **SWAP**, **Fan**, **Thermal**, **Disk**, and **Network** usage — using data from the Linux `/proc` and `/sys` filesystems.

---

## 🎯 Objectives

The goal of this project is to:

- Demonstrate programming logic and adaptability in C++.
- Enhance an existing desktop system monitor by **adding features** and **fixing code**.
- Integrate **Dear ImGui** for real-time graphical user interface rendering.

---

## ⚙️ Features

### 🧠 System Monitor

- OS type, current user, and hostname.
- Total number of tasks and process states.
- CPU information and live performance graph.
- Fan and Thermal tabs with real-time data and adjustable graph settings:
  - FPS control.
  - Y-axis scale control.
  - Start/stop graph animation.

### 💾 Memory & Process Monitor

- RAM, SWAP, and Disk usage with visual indicators.
- Process table with:
  - PID, Name, State, CPU usage (%), Memory usage (%).
- Search/filter box with multi-row selection.

### 🌐 Network Monitor

- IPv4 interfaces (e.g., `lo`, `wlp5s0`).
- RX (Receiver) and TX (Transmitter) tables with:
  - Bytes, Packets, Errors, Drops, etc.
- Dynamic visual display with automatic byte-to-GB/MB/KB conversion (range: 0GB–2GB).

---

## 🧩 Tech Stack

- **Language:** C++  
- **GUI:** [Dear ImGui](https://github.com/ocornut/imgui)  
- **Backend:** SDL2 + OpenGL  
- **Platform:** Linux  
- **Data Source:** `/proc` and `/sys` filesystems  

---

## 🚀 Setup & Run

```bash
sudo apt update
sudo apt install libsdl2-dev g++
make run
```

Developed as part of a System Monitoring project challenge.
Feel free to contribute or modify the app to add new features!

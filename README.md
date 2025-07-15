# Water Distribution Management System

This project was developed as part of the *Design of Algorithms (DA)* course (Spring 2024, FEUP), where we built an **analysis tool for managing a national water supply network**.

## Overview

The goal was to model and analyze a realistic water distribution system using graph-based algorithms. Our tool supports a management team in making decisions regarding supply, demand, and network resilience by answering questions such as:

- Can all cities be fully supplied?
- Which cities are most affected by reservoir or station failures?
- How to redistribute flow to reduce bottlenecks?

To solve this, we implemented:
- **Edmonds-Karp algorithm** for max-flow computations
- Custom **load balancing heuristics** to optimize pipe usage
- **Failure simulations** (removal of reservoirs, pumping stations, and pipes)
- **Graph data structures** tailored to a national-scale water network

## ⚙️ Technologies

- **C++**
- **Doxygen** (for full API documentation)
- CSV data parsing, command-line interface

## 📊 Dataset

The dataset models the **continental Portuguese water supply system**, including:
- Reservoirs
- Pumping Stations
- Delivery Sites (Cities)
- Pipelines (with direction & capacity)

## 🏁 Grade

**Final Grade: 15.05/20**

## Features

- Menu-based CLI to access analysis tools
- Read and parse structured CSV input data
- Calculate max flow to each city
- Identify supply deficits
- Balance network loads
- Simulate failures and analyze impacts

---
Developed by:
Alexandre Lopes
Guilherme Santos
Tomás Silva

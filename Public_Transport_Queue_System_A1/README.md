# Public Transport Queue System: Minibus Taxi Simulation
### C++ Simulation using Linear Data Structures (Queues & Stacks)

## 📌 Project Overview
This project simulates a real-world minibus taxi rank system, a cornerstone of public transport across Africa. Using **Queues and Stacks**, the program manages passenger arrivals and boarding processes for three distinct routes: **Short-distance (S)**, **Long-distance (L)**, and **City routes (C)**.

The simulation tracks passenger flow, boarding times, and taxi departures based on a capacity-filling logic, providing a time-step analysis of rank efficiency.



---

## 🚀 Key Features
* **Route-Specific Queue Management:** Three separate queues manage passengers based on their destination (S, L, or C).
* **Boarding Logic:** Implements processing time delays for each passenger, simulating the time taken to settle into the vehicle.
* **Capacity Tracking:** Taxis have a fixed capacity of **5 passengers**. The system automatically triggers a "departure" and resets the capacity once a taxi is full.
* **File I/O with Error Handling:** Reads passenger data from `taxiData.txt` using a robust `try-catch` block to ensure cross-platform stability (Windows/Mac/Linux).

---

## 📂 Data Structure Implementation
* **Queues (FIFO):** Used to manage passenger arrival order, ensuring that the first person to arrive is the first to board.
* **Stacks (LIFO):** Utilized for [mention specific use case, e.g., managing a stack of boarding passes or undoing last-minute arrivals].
* **Time-Step Simulation:** A discrete-time simulation where each loop iteration represents a single time unit.

---

## 📋 Input & Output Format

### Input Data (`taxiData.txt`)
Data is processed in a comma-separated format: `timecount, route, boarding_time`.
> Example: `1, S, 3` (At time 1, an 'S' route passenger arrives with a 3-unit boarding time).

### Simulation Output
The program outputs a live tabular dashboard at every time step:
| Time Step | Next Passenger | Q Size (S, L, C) | Waiting Q (S, L, C) | Taxi Capacity (S, L, C) |
| :--- | :--- | :--- | :--- | :--- |
| *t* | New arrivals | Total in rank | Currently boarding | Current seats filled |

---

## 🛠 Setup and Installation
1. **Data File Path:** Ensure `taxiData.txt` is located at `C:\data\taxiData.txt` for Windows. If using Mac/Linux, update the path in the source code or ensure the directory structure exists.
2. **Compilation:**
   ```bash
   g++ -std=c++11 main.cpp -o taxi_sim

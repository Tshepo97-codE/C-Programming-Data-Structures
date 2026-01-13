# Smart City Route Management System
### C++ Optimization & Pathfinding with Explainable AI (XAI)

## 📌 Project Overview
The **Smart City Route Management System** is a C++ application designed for urban transport authorities to optimize road networks. The system models city intersections as nodes and roads as edges, providing real-time route optimization, network manipulation, and transparent decision-making through **Explainable AI (XAI)** principles.



---

## 🚀 Key Features
* **Dynamic Network Management:** Add, remove, or update routes (edges) and intersections (nodes) on the fly.
* **Route Optimization:** Implements **Dijkstra’s Algorithm** to find the most efficient paths based on distance or travel time.
* **Algorithm Comparison:** Includes a comparison module between Dijkstra (weighted) and BFS (unweighted) to justify pathfinding efficiency.
* **XAI-Driven Output:** Unlike "black-box" systems, this application explains *why* a specific route was chosen or why a data structure was utilized.
* **Advanced Data Manipulation:** * **Undo/Redo System:** Managed via Stacks to revert accidental network changes.
    * **Hierarchical Storage:** Routes organized by transport zones using Tree structures.

---

## 🛠 Data Structures & Algorithms Applied
This project demonstrates proficiency in several core Computer Science concepts:

| Component | Implementation | Purpose |
| :--- | :--- | :--- |
| **Graph Theory** | Adjacency List / Matrix | Core representation of the city intersections. |
| **Pathfinding** | Dijkstra & BFS | Calculating shortest paths and comparing traversal efficiency. |
| **LIFO Logic** | Stacks | Enabling the "Undo" functionality for network operations. |
| **Storage** | STL Vectors & Lists | Dynamic storage and manipulation of route data. |
| **Organization** | Binary Trees / Sets | Managing Zone Hierarchies and unique route storage. |
| **Optimization** | STL Functors | Custom sorting logic for diverse criteria (time, cost, distance). |

---

## 🔍 Explainable AI (XAI) Integration
A core requirement of this system is **Transparency**. The code and the UI provide clear reasoning for every decision:
* **Algorithm Transparency:** When a path is found, the system outputs the number of nodes visited and the logic behind the selection (e.g., "Route A chosen because it is 2km shorter than Route B").
* **Logic Documentation:** Every critical function includes an `// XAI:` comment block explaining the reasoning to ensure the code is maintainable and the logic is accessible to non-programmers.

---

## 📋 System Menu
The application features a comprehensive menu-driven interface for city officials:
1.  **Display City Network:** View the current graph structure.
2.  **Add New Route:** Connect two intersections with specific weights.
3.  **Remove Route:** Delete existing infrastructure data.
4.  **Find Shortest Path (Dijkstra):** Calculate optimal paths between locations.
5.  **Find Routes by Criteria:** Search for specific routes based on length or time.
6.  **Sort and Display Routes:** Rank routes using custom comparators.
7.  **Display Zone Hierarchy:** View the hierarchical organization of transport zones.
8.  **AI Congestion Prediction:** Predict traffic peaks based on time-of-day data.
9.  **Compare Algorithms:** Benchmarking Dijkstra vs. BFS performance.
10. **Simulate Traffic Flow:** Model the movement of vehicles through the network.
11. **Undo Last Operation:** Revert the previous network change using stack logic.
12. **Exit**

---

## ⚙️ Setup & Execution
### How to Run
1. Clone this repository.
2. Compile using G++:
   ```bash
   g++ -std=c++17 main.cpp -o smart_city_system

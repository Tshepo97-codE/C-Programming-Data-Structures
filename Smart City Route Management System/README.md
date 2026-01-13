# Smart City Route Management System
### C++ Optimization & Pathfinding with Explainable AI (XAI)

## 📌 Project Overview
The **Smart City Route Management System** is a C++ application designed for urban transport authorities to optimize road networks. The system models city intersections as nodes and roads as edges, providing real-time route optimization, network manipulation, and transparent decision-making through **Explainable AI (XAI)** principles.



---

## 🚀 Key Features
* **Dynamic Network Management:** Add, remove, or update routes (edges) and intersections (nodes) on the fly.
* **Route Optimization:** Implements **Dijkstra’s Algorithm** to find the most efficient paths based on distance or travel time.
* **XAI-Driven Output:** Unlike "black-box" systems, this application explains *why* a specific route was chosen or why a data structure was utilized.
* **Advanced Data Manipulation:** * **Sorting/Searching:** Rank routes by cost or time using custom **STL Functors**.
    * **Undo/Redo System:** (Optional) Managed via Stacks/Queues for batch updates.
    * **Hierarchical Storage:** Routes organized by transport zones using Tree structures.

---

## 🛠 Data Structures & Algorithms Applied
This project demonstrates proficiency in several core Computer Science concepts:

| Component | Implementation | Purpose |
| :--- | :--- | :--- |
| **Graph Theory** | Adjacency List / Matrix | Core representation of the city intersections. |
| **Pathfinding** | Dijkstra’s Algorithm | Calculating the shortest path between two points. |
| **Storage** | STL Vectors & Lists | Dynamic storage and manipulation of route data. |
| **Organization** | Binary Trees / Sets | Hierarchical zoning and ensuring unique route IDs. |
| **Optimization** | STL Functors | Custom sorting logic (e.g., sorting by congestion vs. distance). |

---

## 🔍 Explainable AI (XAI) Integration
A core requirement of this system is **Transparency**. The code and the UI provide clear reasoning for every decision:
* **Algorithm Transparency:** When a path is found, the system outputs the number of nodes visited and the logic behind the selection (e.g., "Route A chosen because it is 2km shorter than Route B").
* **Logic Documentation:** Every critical function includes an `// XAI:` comment block explaining the reasoning to ensure the code is maintainable and the logic is accessible to non-programmers.



---

## 📋 System Menu
The application features a menu-driven interface for city officials:
1. **Add a Route:** Connect two intersections with a specific weight.
2. **Remove/Update Route:** Modify existing infrastructure data.
3. **View Network:** Display the current city graph.
4. **Find Shortest Path:** Run Dijkstra’s algorithm between two locations.
5. **Sort Routes:** Rank routes based on length or travel time.
6. **Exit**

---

## ⚙️ Setup & Deliverables
### Deliverables
* **Source Code:** Fully commented C++ implementation.
* **XAI Documentation:** Inline comments and a final summary of logic.
* **Problem Analysis:** A deep dive into why specific algorithms (like Dijkstra) were chosen over alternatives.

### How to Run
1. Clone this repository.
2. Compile using G++:
   ```bash
   g++ -std=c++17 main.cpp -o smart_city_system

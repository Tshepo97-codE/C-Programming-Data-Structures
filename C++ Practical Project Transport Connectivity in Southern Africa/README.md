# Transport Connectivity in Southern Africa
### C++ Graph-Based Network Analysis Project

## 📌 Project Overview
This project models a simplified transport network across Southern Africa using **Graph Theory** in C++. The application represents major cities (Windhoek, Gaborone, Johannesburg, Harare, and Maputo) as vertices and the roads connecting them as weighted edges. 

The goal of this project is to demonstrate graph traversals for reachability and pathfinding algorithms for optimal route planning, all while maintaining **Explainable AI (XAI)** standards.



---

## 🚀 Features
* **Dual Graph Representation:** Uses **Adjacency Lists** for efficiency and **Adjacency Matrices** for clear visualization of city connections.
* **Reachability Analysis:** Implements **Breadth-First Search (BFS)** to identify all reachable destinations from a starting city.
* **Route Optimization:** Implements **Dijkstra’s Algorithm** to calculate the shortest geographical distance and the specific path between two cities.
* **XAI Documentation:** Every logical block is commented to explain "the why" behind the code, making the logic accessible to non-programmers.

---

## 📊 Technical Requirements Met
This project was built according to the following rubric:
* **Graph Representation:** Full adjacency list and formatted matrix display.
* **Data Input:** Real-world modeling of 5+ Southern African capital cities and distances.
* **BFS Traversal:** Functional traversal showing the order of city visitation.
* **Dijkstra’s Algorithm:** Calculation of the absolute shortest path and city sequence.
* **Visual Output:** User-friendly console interface showing clear road connections.
* **XAI & Reflection:** Detailed documentation of logic and GenAI usage.

---

## 🤖 GenAI and XAI Usage Disclosure

### Explainable AI (XAI) Practice
In alignment with project requirements, this code utilizes XAI practices. Each variable, data structure, and algorithmic step is documented with clear explanations to ensure the logic is transparent and human-readable.

### AI Reflection
**Prompts Used:**
* *"Implement a weighted adjacency list in C++ for a city transport network."*
* *"Explain the step-by-step logic of Dijkstra's algorithm for a non-programmer."*
* *"Format a C++ console output to display a 5x5 adjacency matrix clearly."*

**Reflection:**
* **What worked:** AI was highly effective at generating the boilerplate for the adjacency matrix and providing the initial structure for the BFS queue.
* **Challenges:** The AI initially suggested a version of Dijkstra's that did not track the "previous" nodes, making it impossible to reconstruct the path. I had to manually implement a `parent` array to store the sequence of cities.
* **Adjustments:** I refined the AI-generated comments to focus more on *logic explanation* (XAI) rather than just technical syntax to meet the specific "non-programmer" requirement of the brief.

---

## 🛠 How to Run
1. Ensure you have a C++ compiler installed (e.g., G++ or Clang).
2. Clone the repository.
3. Compile the source code: `g++ main.cpp -o transport_network`
4. Run the executable: `./transport_network`

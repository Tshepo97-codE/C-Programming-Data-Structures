
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For sort, find and other algorithms
#include <queue>
#include <limits> // For representing infinity in Dijkstra's algorithm
#include <utility> // For pair data types
#include <iomanip> // For formatting outputs

using namespace std;

const int max_cities = 5;
const int infinity_distance = 999999; // Represents infinity distance (no connection)
const int no_connection = -1; // Value indicating no direct road exists

vector<vector<pair<int, int>>> adjacencyList; // This is a vector of vectors containing pairs
vector<vector<int>> adjacencyMatrix; // 2D vector where matrix[i][j] represents distance from city i to city j
vector<string> cityNames; // Vector to store city names

int numberOfCities; // Number of cities in the graph
void bfsTraversal(int startCity);
void dijkstraAlgorithm(int source, int destination);  // Missing declaration
void displayDijkstraResults(int source, int destination, const vector<int>& distances, const vector<int>& parent);  // Missing declaration

void initializeCities() {
    cityNames = {"Johannesburg", "Cape Town", "Windhoek", "Gaborone", "Harare"};
    numberOfCities = 5;
    adjacencyList.resize(numberOfCities);
    adjacencyMatrix.resize(numberOfCities, vector<int>(numberOfCities, infinity_distance));

    for(int i = 0; i < numberOfCities; i++){
        adjacencyMatrix[i][i] = 0; // Distance to self is zero
    }
    cout << "Initialized Southern African Transport Network with "  << numberOfCities << " major cities." << endl;
    cout << "Cities: ";
    for(int i = 0; i < numberOfCities; i++){
        cout << cityNames[i];
        if(i < numberOfCities - 1) cout << ", ";
    }
    cout << "\n\n";
}

void addRoadConnection(int city1, int city2, int distance){
    adjacencyList[city1].push_back(make_pair(city2, distance));
    adjacencyList[city2].push_back(make_pair(city1, distance));

    adjacencyMatrix[city1][city2] = distance;
    adjacencyMatrix[city2][city1] = distance; // Bidirectional road
}

void initializeRoadNetwork(){
    cout << "Initializing road network with realistic distances...\n";

    addRoadConnection(0, 1, 1400); // Johannesburg to Cape Town via N1
    addRoadConnection(0, 2, 1050); // Johannesburg to Windhoek via A2/N14
    addRoadConnection(0, 3, 360);  // Johannesburg to Gaborone  via N4
    addRoadConnection(0, 4, 600);  // Johannesburg to Harare (N1 north)

    // Cape town additional connections
    addRoadConnection(1, 2, 1300); // Cape Town to Windhoek via N7
    // Windhoek additional connections
    addRoadConnection(2, 3, 1100); // Windhoek to Gaborone (Trans-Kalahari Highway)
    // Gaborone additional connections
    addRoadConnection(3, 4, 550); // Gaborone to Harare via A1/N1

    cout << "Road network initialized successfully!\n";
    cout << "Total connections created: 7 major routes\n";
}

void displayCityList(){
    cout << "=== CITIES IN TRANSPORT NETWORK ===\n";
    for(int i = 0; i < numberOfCities; i++){
        cout << "[" << i << "]" << cityNames[i] << "\n";
    }
    cout << "\n";
}

void displayAdjacencyList(){
    cout << "=== ADJACENCY LIST REPRESENTATION ===\n";
    cout << "Shows direct road connections from each city:\n\n";

    // Loop through each city
    for(int i = 0; i < numberOfCities; i++){
        cout << cityNames[i] << " connects directly to: \n";
        if(adjacencyList[i].empty()){
            cout << " No direct connections \n";
        } else {
            for(const auto& connection : adjacencyList[i]){
                int destinationCity = connection.first;
                int distance = connection.second;

                cout << " - " << cityNames[destinationCity] << " (" << distance << " km)\n";
            }
        }
        cout << "\n";
    }
}

void displayAdjacencyMatrix() {
    cout << " === ADJACENCY MATRIX REPRESENTATION ===\n";
    cout << "Direct distance between cities (km):\n";
    cout << "INF means no direct road connection exists\n\n";

    cout << setw(18) << " "; // Space for row headers
    for(int j = 0; j < numberOfCities; j++) {
        cout << setw(10) << cityNames[j].substr(0, 13); // First 6 chars of city name
    }
    cout << "\n";

    // Display separator line
    cout << setw(15) << " ";
    for(int j = 0; j < numberOfCities; j++) {
        cout << setw(12.5) << "-------------";
    }
    cout << "\n";

    // Display matrix rows with data
    for(int i = 0; i < numberOfCities; i++) {
        cout << setw(14) << cityNames[i].substr(0, 13) << "|";

        // Display each cell in the row
        for(int j = 0; j < numberOfCities; j++) {
            if(i == j) {
                cout << setw(11) << "0"; // Distance from city to itself
            } else if(adjacencyMatrix[i][j] == infinity_distance) {
                cout << setw(11) << "INF"; // No direct connection
            } else {
                cout << setw(11) << adjacencyMatrix[i][j]; // Actual distance
            }
        }
        cout << "\n";
    }
    cout << "\n";
}


void displayCompleteNetwork() {
    cout << "\n";
    cout << "+============================================================+\n";
    cout << "|         SOUTHERN AFRICA TRANSPORT NETWORK OVERVIEW         |\n";
    cout << "+============================================================+\n";
    cout << "\n";

    // Display all components of our network
    displayCityList();
    displayAdjacencyList();
    displayAdjacencyMatrix();

    cout << "Network Statistics:\n";
    cout << "- Total Cities: " << numberOfCities << "\n";

    // Count total connections
    int totalConnections = 0;
    for(int i = 0; i < numberOfCities; i++) {
        totalConnections += adjacencyList[i].size();
    }
    cout << "- Total Road Connections: " << totalConnections / 2 << "\n\n";
}


int getUserCityChoice(const string& prompt){
    int choice;

    cout << prompt << "\n";
    displayCityList();
    cout << "Enter city number (0-" << (numberOfCities - 1) << ") or -1 to cancel: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    // Validate input
    if(choice >= 0 && choice < numberOfCities){
        return choice;
    } else if(choice == -1){
        cout << "Operation canceled. \n";
        return -1;
    } else {
        cout << "Invalid choice! Please enter a number between 0 and " << (numberOfCities - 1) << "\n";
        return -1;
    }
}

// Executes BFS traversal starting from a user-selected city.
void performBFS() {
    cout << "\n === BREADTH-FIRST SEARCH (BFS) TRAVERSAL ===\n";
    cout << "Find all cities reachable from a starting city.\n";

    int startCity = getUserCityChoice("Select starting city for BFS:");
    if(startCity == -1) { return; }// Canceled

    cout << "\n --- BFS Results ---\n";
    bfsTraversal(startCity);
}

void bfsTraversal(int startCity) {

    // Initialize BFS data structures
    vector<bool> visited(numberOfCities, false);
    queue<int> bfsQueue;
    vector<int> visitOrder;
    vector<int> distances;
    vector<int> parent;

    // Initialize parent and distance tracking
    parent.resize(numberOfCities, -1);
    distances.resize(numberOfCities, 0);

    // Start BFS from the selected city
    bfsQueue.push(startCity);
    visitOrder.push_back(startCity);
    visited[startCity] = true; // Mark starting city as visited

    cout << "Starting BFS exploration from: " << cityNames[startCity] << "\n";
    cout << "Discovery order: \n";
    cout << "1. " << cityNames[startCity] << " (starting city)\n";

    int discoveryCount = 1;

    // Main BFS loop
    while(!bfsQueue.empty()){
        int currentCity = bfsQueue.front();
        bfsQueue.pop();

        // Explore all adjacent cities
        for(const auto& neighbor : adjacencyList[currentCity]){
            int neighborCity = neighbor.first;
            int distance = neighbor.second;

            if(!visited[neighborCity]){
                visited[neighborCity] = true; // Mark as visited
                bfsQueue.push(neighborCity); // Add to queue for processing
                visitOrder.push_back(neighborCity); // Record visit order
                parent[neighborCity] = currentCity; // Remember how we got here
                distances[neighborCity] = distances[currentCity] + distance;

                discoveryCount++;
               cout << discoveryCount << ". " << cityNames[neighborCity]
                     << " (reached from " << cityNames[currentCity]
                     << ", total distance: " << distances[neighborCity] << " km)\n";
            }
        }
    }

    // Display summary of BFS results
    cout << "\n--- BFS Summary ---\n";
    cout << "Cities reachable from " << cityNames[startCity] << ": "
    << visitOrder.size() << " out of " << numberOfCities << "total cities \n";

    // Unreachable cities check
    vector<int> unreachable;
    for(int i = 0; i < numberOfCities; i++){
        if(!visited[i]){
            unreachable.push_back(i);
        }
    }
    if(unreachable.empty()){
        cout << "All cities are reachable from " << cityNames[startCity] << ":\n";
        cout << "This means the transport network is fully connected. \n";
    } else {
        cout << " Unreachable cities: ";
        for(int i = 0; i < unreachable.size(); i++){
            cout << cityNames[unreachable[i]];
            if(i < unreachable.size() - 1) cout << ", ";
        }
        cout << "\n This indicates disconnected parts in the network. \n";
    }

    // Display reachable cities with their distances
    cout << "\nDetailed reachability from " << cityNames[startCity] << ":\n";
    for(int i = 0; i < numberOfCities; i++){
        if(visited[i]){
            if(i == startCity){
                cout << ". " << cityNames[i] << ": 0 Km (starting city)\n";
            } else {
                cout << ". " << cityNames[i] << ": " << distances[i] << " Km";
                // Show path
                cout << " (path: ";
            vector<int> path;
        int current = i;
    while(current != -1){
        path.push_back(current);
        current = parent[current];
    } reverse(path.begin(), path.end());

    for(int j = 0; j < path.size(); j++){
        cout << cityNames[path[j]];
        if(j < path.size() - 1) cout << " -> ";
    }
    cout << ")\n";
            }
        }
    }
    cout << "\n";
}

void performDijkstra() {
         cout << "\n=== DIJKSTRA'S SHORTEST PATH ALGORITHM ===\n";
    cout << "Find the shortest route and distance between any two cities\n\n";

    // STEP 5A: Get source city
    int sourceCity = getUserCityChoice("Select starting city (source):");
    if(sourceCity == -1) {
        return; // User canceled or invalid input
    }

    // STEP 5B: Get destination city
    int destinationCity = getUserCityChoice("Select destination city:");
    if(destinationCity == -1) {
        return; // User canceled or invalid input
    }

    // STEP 5C: Check for same city selection
    if(sourceCity == destinationCity) {
        cout << "Source and destination are the same city!\n";
        cout << "Distance: 0 km\n";
        cout << "Path: " << cityNames[sourceCity] << "\n\n";
        return;
    }

    // STEP 5D: Perform Dijkstra's algorithm
    cout << "\n--- Dijkstra's Algorithm Results ---\n";
    cout << "Finding shortest path from " << cityNames[sourceCity]
         << " to " << cityNames[destinationCity] << "...\n\n";

    dijkstraAlgorithm(sourceCity, destinationCity);
}

void dijkstraAlgorithm(int source, int destination) {
    // Initialize Dijkstra data structures

    vector<int> distances(numberOfCities, infinity_distance);    // All distances start as infinite
    vector<bool> visited(numberOfCities, false);             // No cities visited yet
    vector<int> parent(numberOfCities, -1);                  // No parent relationships yet


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize starting conditions
    distances[source] = 0;              // Distance to source is 0
    pq.push(make_pair(0, source));      // Add source to queue with distance 0

    cout << "Step-by-step Dijkstra execution:\n";
    cout << "1. Starting from " << cityNames[source] << " (distance: 0)\n";

    int step = 1;

    // Main Dijkstra loop
    while(!pq.empty()) {
        // Get the unvisited city with minimum distance
        int currentDistance = pq.top().first;
        int currentCity = pq.top().second;
        pq.pop();

        // Skip if we've already processed this city
        if(visited[currentCity]) {
            continue;
        }

        // Mark current city as permanently solved
        visited[currentCity] = true;
        step++;

        cout << step << ". Processing " << cityNames[currentCity]
             << " (confirmed shortest distance: " << currentDistance << " km)\n";

        // Early termination if we reached destination

        if(currentCity == destination) {
            cout << "   -> Destination reached! Shortest path found.\n";
            break;
        }

        // Examine all neighbors of current city

        for(const auto& connection : adjacencyList[currentCity]) {
            int neighborCity = connection.first;
            int roadDistance = connection.second;

            // Calculate potential new distance to neighbor

            int newDistance = currentDistance + roadDistance;

            // Relax the edge if we found a shorter path

            if(newDistance < distances[neighborCity]) {
                distances[neighborCity] = newDistance;
                parent[neighborCity] = currentCity;
                pq.push(make_pair(newDistance, neighborCity));

                cout << "   -> Found shorter path to " << cityNames[neighborCity]
                     << ": " << newDistance << " km (via " << cityNames[currentCity] << ")\n";
            }
        }
    }

    // Display final results
    displayDijkstraResults(source, destination, distances, parent);
}

// DisplayDijkstraResults()
void displayDijkstraResults(int source, int destination,
                           const vector<int>& distances, const vector<int>& parent) {
    cout << "\n=== DIJKSTRA'S ALGORITHM RESULTS ===\n";

    // Check if destination is reachable

    if(distances[destination] == infinity_distance) {
        cout << " No path exists from " << cityNames[source]
             << " to " << cityNames[destination] << "\n";
        cout << "These cities are in disconnected parts of the network.\n\n";
        return;
    }

    // Display shortest distance
    cout << " Shortest path found!\n";
    cout << "From: " << cityNames[source] << "\n";
    cout << "To: " << cityNames[destination] << "\n";
    cout << "Shortest Distance: " << distances[destination] << " km\n\n";

    vector<int> shortestPath;
    int current = destination;

    // Build path by following parent links backwards
    while(current != -1) {
        shortestPath.push_back(current);
        current = parent[current];
    }

    // Reverse to get source → destination order
    reverse(shortestPath.begin(), shortestPath.end());

    // Display the complete path with distances
    cout << "Shortest Path Route:\n";
    for(int i = 0; i < shortestPath.size(); i++) {
        cout << cityNames[shortestPath[i]];

        if(i < shortestPath.size() - 1) {
            // Find the distance between consecutive cities in the path
            int currentCity = shortestPath[i];
            int nextCity = shortestPath[i + 1];
            int segmentDistance = 0;

            // Look up the direct distance between consecutive cities
            for(const auto& connection : adjacencyList[currentCity]) {
                if(connection.first == nextCity) {
                    segmentDistance = connection.second;
                    break;
                }
            }

            cout << " -> " << cityNames[nextCity] << " (" << segmentDistance << " km)";
            if(i < shortestPath.size() - 2) cout << "\n     \n";
        }
    }

    cout << "\n\nPath Summary:\n";
    cout << "Total Distance: " << distances[destination] << " km\n";
    cout << "Number of Cities: " << shortestPath.size() << "\n";
    cout << "Number of Road Segments: " << shortestPath.size() - 1 << "\n";

    // Show distances to all cities from source
    cout << "\nShortest distances from " << cityNames[source] << " to all cities:\n";
    for(int i = 0; i < numberOfCities; i++) {
        if(i == source) {
            cout << "-> " << cityNames[i] << ": 0 km (starting city)\n";
        } else if(distances[i] == infinity_distance) {
            cout << "-> " << cityNames[i] << ": ∞ (unreachable)\n";
        } else {
            cout << "-> " << cityNames[i] << ": " << distances[i] << " km\n";
        }
    }
    cout << "\n";
}

void displayWelcomeMessage() {
    cout << "\n";
    cout << "+==================================================================+\n";
    cout << "|                                                                  |\n";
    cout << "|       SOUTHERN AFRICA TRANSPORT NETWORK ANALYSIS SYSTEM          |\n";
    cout << "|                                                                  |\n";
    cout << "|  A Graph-Based Program for Route Planning and Network Analysis   |\n";
    cout << "|                                                                  |\n";
    cout << "|  Features:                                                       |\n";
    cout << "|   - 5 Major Southern African Cities                              |\n";
    cout << "|   - Realistic Highway Distances                                  |\n";
    cout << "|   - Breadth-First Search (BFS) for Reachability                  |\n";
    cout << "|   - Dijkstra's Algorithm for Shortest Paths                      |\n";
    cout << "|   - Complete Network Visualization                               |\n";
    cout << "|                                                                  |\n";
    cout << "+==================================================================+\n";
    cout << "\n";
    cout << "Cities in Network: Johannesburg, Cape Town, Windhoek, Gaborone, Harare\n";
    cout << "Ready to explore Southern Africa's transport connections!\n\n";
}

void displayMainMenu() {
    cout << "+-----------------------------------------------------------+\n";
    cout << "|                        MAIN MENU                          |\n";
    cout << "+-----------------------------------------------------------+\n";
    cout << "|  [1] Display Network Structure                            |\n";
    cout << "|      -> View adjacency list and matrix representations    |\n";
    cout << "|                                                           |\n";
    cout << "|  [2] Find Reachable Cities (BFS)                          |\n";
    cout << "|      -> Discover all cities accessible from a starting pt |\n";
    cout << "|                                                           |\n";
    cout << "|  [3] Find Shortest Path (Dijkstra)                        |\n";
    cout << "|      -> Calculate minimum distance route between cities   |\n";
    cout << "|                                                           |\n";
    cout << "|  [4] Add Additional Road Connection                       |\n";
    cout << "|      -> Expand the network with new routes                |\n";
    cout << "|                                                           |\n";
    cout << "|  [5] Exit Program                                         |\n";
    cout << "|      -> Close the transport network system                |\n";
    cout << "+-----------------------------------------------------------+\n";
    cout << "\nEnter your choice (1-5): ";
}

void addUserConnection() {
    cout << "\n=== ADD NEW ROAD CONNECTION ===\n";
    cout << "Add a new bidirectional road between two cities\n\n";

    // Display current network for reference
    cout << "Current cities:\n";
    displayCityList();

    // Get connection details from user
    int city1 = getUserCityChoice("Select first city:");
    if(city1 == -1) return;

    int city2 = getUserCityChoice("Select second city:");
    if(city2 == -1) return;

    // Check if connection already exists
    bool connectionExists = false;
    for(const auto& connection : adjacencyList[city1]) {
        if(connection.first == city2) {
            connectionExists = true;
            cout << "A road already exists between " << cityNames[city1]
                 << " and " << cityNames[city2] << " (distance: "
                 << connection.second << " km)\n";

            char choice;
            cout << "Do you want to update the distance? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            if(choice != 'y' && choice != 'Y') {
                cout << "Operation canceled.\n\n";
                return;
            }
            break;
        }
    }

    // Get distance for the new connection
    int distance;
    cout << "Enter distance between " << cityNames[city1]
         << " and " << cityNames[city2] << " (km): ";
    cin >> distance;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    // Validate distance input
    if(distance <= 0 || distance > 10000) {
        cout << "Invalid distance! Please enter a value between 1 and 10000 km.\n\n";
        return;
    }

    // Add or update the connection
    if(connectionExists) {
        // Update existing connection
        for(auto& connection : adjacencyList[city1]) {
            if(connection.first == city2) {
                connection.second = distance;
                break;
            }
        }
        for(auto& connection : adjacencyList[city2]) {
            if(connection.first == city1) {
                connection.second = distance;
                break;
            }
        }
        adjacencyMatrix[city1][city2] = distance;
        adjacencyMatrix[city2][city1] = distance;

        cout << " Updated road connection:\n";
    } else {
        // Add new connection
        addRoadConnection(city1, city2, distance);
        cout << " Added new road connection:\n";
    }

    cout << "   " << cityNames[city1] << " <-> " << cityNames[city2]
         << " (" << distance << " km)\n\n";

    // Ask if user wants to see updated network
    char viewChoice;
    cout << "Would you like to see the updated network structure? (y/n): ";
    cin >> viewChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    if(viewChoice == 'y' || viewChoice == 'Y') {
        displayCompleteNetwork();
    }
}

void handleInvalidInput() {
    cout << "\n Invalid selection! Please choose a number between 1 and 5.\n\n";

    // Clear any remaining characters in input buffer
    cin.clear();
    cin.ignore(10000, '\n');
}

void displayGoodbye() {
    cout << "\n";
    cout << "+==================================================================+\n";
    cout << "|                                                                  |\n";
    cout << "|              Thank you for using the                             |\n";
    cout << "|         SOUTHERN AFRICA TRANSPORT NETWORK SYSTEM                 |\n";
    cout << "|                                                                  |\n";
    cout << "|  You explored:                                                   |\n";
    cout << "|    - Graph representations (adjacency lists & matrices)          |\n";
    cout << "|    - Breadth-First Search for network connectivity               |\n";
    cout << "|    - Dijkstra's algorithm for shortest path calculations         |\n";
    cout << "|                                                                  |\n";
    cout << "|  These algorithms are fundamental to:                            |\n";
    cout << "|    - GPS navigation systems                                      |\n";
    cout << "|    - Social network analysis                                     |\n";
    cout << "|    - Internet routing protocols                                  |\n";
    cout << "|    - Supply chain optimization                                   |\n";
    cout << "|                                                                  |\n";
    cout << "|                    Happy travels!                                |\n";
    cout << "|                                                                  |\n";
    cout << "+==================================================================+\n";
    cout << "\n";
}


int main() {
    // Program initialization
    displayWelcomeMessage();

    cout << "Initializing transport network...\n";
    initializeCities();        // Set up the 5 Southern African cities
    initializeRoadNetwork();   // Create realistic road connections
    cout << " System ready for use!\n\n";

    // Main program loop
    int choice;
    bool programRunning = true;

    while(programRunning) {
        displayMainMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        // Process user selection
        switch(choice) {
            case 1:
                displayCompleteNetwork();
                break;

            case 2:
                performBFS();
                break;

            case 3:
                performDijkstra();
                break;

            case 4:
                addUserConnection();
                break;

            case 5:
                cout << "\nShutting down transport network system...\n";
                displayGoodbye();
                programRunning = false;
                break;

            default:
                handleInvalidInput();
                break;
        }

        // Pause between operations (except on exit)
        if(programRunning && choice >= 1 && choice <= 4) {
            cout << "Press Enter to continue...";
            // cin.ignore();
            cin.get();
            cout << "\n" << string(50, '=') << "\n";
        }
    }

    // Clean program termination
    return 0;
}


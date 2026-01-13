

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>
#include <stack>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

const int TAXI_CAPACITY = 5;
struct Passenger{
    char routeType;
    int boardingTime;
    int arrivalTime;
    };

    queue<Passenger> shortQueue;
    queue<Passenger> longQueue;
    queue<Passenger> cityQueue;

struct TaxiRouteState{
    queue<Passenger> passengerQueue;
    vector<Passenger> onBoardList;
    bool isBoarding = false;
    int boardingTimer = 0;
    Passenger currentBoardingPassenger;
    int currentCapacity = TAXI_CAPACITY;
    string status = "Waiting";

};

// Short-distance route ('S'), Long-distance route ('L'), City route ('C').
TaxiRouteState shortTaxi, longTaxi, cityTaxi;

bool allProcessingComplete(int arrivalTracker, const vector<Passenger>& allPassengers) {
    // Check if all passengers have arrived and all queues are empty.
    bool allArrived = (arrivalTracker >= allPassengers.size());
    bool allQueuesEmpty = shortTaxi.passengerQueue.empty() && longTaxi.passengerQueue.empty() && cityTaxi.passengerQueue.empty();
    bool noActiveBoarding = !shortTaxi.isBoarding && !longTaxi.isBoarding && !cityTaxi.isBoarding;

    return allArrived && allQueuesEmpty && noActiveBoarding;
}

// This is a helper function to print queue content as string.
string getWaitingQueue(queue<Passenger> q){
    stringstream ss;
    if (q.empty()) return "0";
    while(!q.empty()){
        ss << q.front().routeType << "(" << q.front().boardingTime << ")";
        q.pop(); // copy so original queue remains intact.
    }
    return ss.str();
}

void printTableHeader(){
    cout << left
    << setw(6)  << "Time"
    << setw(15) << "Next"
    << setw(6)  << "S"
    << setw(6)  << "L"
    << setw(6)  << "C"
    << setw(14) << "WQS"
    << setw(14) << "WQL"
    << setw(14) << "WQC"
    << setw(8)  << "CS"
    << setw(10) << "StatS"
    << setw(8)  << "CL"
    << setw(10) << "StatL"
    << setw(8)  << "CC"
    << setw(10) << "StatC"
    << endl;
}

// This will print the table row.
void printSimulationRow(int timeInstance, const string& newArrivals,
                       TaxiRouteState& shortTaxi, TaxiRouteState& longTaxi, TaxiRouteState& cityTaxi) {
    cout << left
    << setw(6) << timeInstance
    << setw(15) << newArrivals
    << setw(6) << shortTaxi.passengerQueue.size()
    << setw(6) << longTaxi.passengerQueue.size()
    << setw(6) << cityTaxi.passengerQueue.size()
    << setw(14) << getWaitingQueue(shortTaxi.passengerQueue)
    << setw(14) << getWaitingQueue(longTaxi.passengerQueue)
    << setw(14) << getWaitingQueue(cityTaxi.passengerQueue)
    << setw(8) << shortTaxi.currentCapacity  // Show current capacity.
    << setw(10) << shortTaxi.status         // Show status.
    << setw(8) << longTaxi.currentCapacity
    << setw(10) << longTaxi.status
    << setw(8) << cityTaxi.currentCapacity
    << setw(10) << cityTaxi.status
    << endl;
}

void processTaxiRoute(TaxiRouteState &taxiState, char routeLabel) {
     if (taxiState.status == "Departed") {
        taxiState.onBoardList.clear();
        taxiState.currentCapacity = TAXI_CAPACITY;
        taxiState.status = "Waiting";
        
    }
    if (taxiState.isBoarding) {
        taxiState.boardingTimer--;

        if (taxiState.boardingTimer <= 0) {
            taxiState.onBoardList.push_back(taxiState.currentBoardingPassenger);
            taxiState.currentCapacity--;  // Decrease capacity.
            taxiState.status = "Board";   // Set status to Board.
            taxiState.isBoarding = false;

            if (taxiState.currentCapacity <= 0) {  // Check if taxi is full.
                taxiState.status = "Departed";

            }
        }
    }

    if (!taxiState.isBoarding && !taxiState.passengerQueue.empty() && taxiState.currentCapacity > 0 && taxiState.currentCapacity > 0 && taxiState.status != "Departed") {
        taxiState.currentBoardingPassenger = taxiState.passengerQueue.front();
        taxiState.passengerQueue.pop();
        taxiState.boardingTimer = taxiState.currentBoardingPassenger.boardingTime;
        taxiState.isBoarding = true;
    }
}
const int MAX_TIME = 50; //Boarding time limit.

void runSimulation(vector<Passenger>& allPassengers) {
    size_t arrivalTracker = 0; // To track passengers already added.
    bool simulationActive = true;

    printTableHeader();

    for(int timeInstance = 0; simulationActive; ++timeInstance){
        stringstream newArrivalsStream;

    // This is to check for the new arrival at each instance.
    while(arrivalTracker < allPassengers.size() && allPassengers[arrivalTracker].arrivalTime == timeInstance){
        Passenger p = allPassengers[arrivalTracker];
        newArrivalsStream << p.routeType << "(" << p.boardingTime << ")";

        switch(p.routeType){
        case 'S':
            shortTaxi.passengerQueue.push(p);
            break;
        case 'L':
            longTaxi.passengerQueue.push(p);
            break;
        case 'C':
            cityTaxi.passengerQueue.push(p);
            break;
        default:
            cout << "Route type not found!" << endl;
        }
        arrivalTracker++;
    }
    processTaxiRoute(shortTaxi, 'S');
    processTaxiRoute(longTaxi, 'L');
    processTaxiRoute(cityTaxi, 'C');

    // Step 3: Display queue and onboard info.
    printSimulationRow(timeInstance, newArrivalsStream.str(), shortTaxi, longTaxi, cityTaxi);

    // Check if simulation should end.
    if(allProcessingComplete(arrivalTracker, allPassengers)) {
        simulationActive = false;
        cout << "\nSimulation ended at time " << timeInstance
             << " - No more passengers to process." << endl;
        }

    // Safety check to prevent infinite loop.
    if(timeInstance > 1000) {  // Adjust this value as needed.
        cerr << "Warning: Simulation terminated after 1000 time units" << endl;
        simulationActive = false;
        }
    }
}

//This function is for reading the input file.
vector<Passenger> readFileData(){
    vector<Passenger> passengerList; // Stores TaxiData in vector.
    const string filename = "C:\\data\\taxiData.txt"; // Hardcore path

    ifstream file(filename); // Initialise and open files in one step.

    try{
        if (!file.is_open()){
            throw runtime_error("Unable to open input file." + filename);
        }
        //Do something with each line.
        string line;
        while (getline(file, line)){
            if(line.empty()) continue;

            line.erase(remove(line.begin(), line.end(), '\r'), line.end());

            stringstream ss(line);
            string timeCount, route, boardTime;

            //Is to read comma-separated values.
            if (!getline(ss, timeCount, ',')) continue;
            if (!getline(ss, route, ',')) continue;
            getline(ss, boardTime, ',');

        try{
            auto trim = [](string& s){
                s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch){return !isspace(ch);}));
                s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {return !isspace(ch);}).base(), s.end());
            };

            trim(timeCount);
            trim(route);
            trim(boardTime);

            int arrivalTime = stoi(timeCount); //Converting string to int.
            char routeType = route.empty() ? '?' : route[0];
            int boardingTime = boardTime.empty() ? 0 : stoi(boardTime); //Converting string to int.

            passengerList.push_back({routeType, boardingTime, arrivalTime});
         } catch (const invalid_argument&) {
                continue;
            } catch (const out_of_range&) {
                continue;
            }
        }
    } catch (const exception& e) {
        if (file.is_open()) file.close();
        cerr << "Error: " << e.what() << endl;
        throw;
    }

    return passengerList;
}

int main() {
    try {
        vector<Passenger> allPassengers = readFileData();
        runSimulation(allPassengers);
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
    return 0;
}


#include "TrainNetwork.h"

#include <queue>
#include <algorithm>


// ==========================================
// ADD TRAIN ROUTE
// ==========================================

void TrainNetwork::addTrainRoute(
    Graph& city,
    int trainNumber,
    string routeName,
    vector<int> stations,
    int travelTime,
    int capacity,
    string startTime,
    string endTime
)
{
    // Check that the route has at least
    // two stations

    if (stations.size() < 2)
    {
        cout << "Invalid train route!"
             << endl;

        return;
    }


    // Check travel time

    if (travelTime <= 0)
    {
        cout << "Invalid travel time!"
             << endl;

        return;
    }


    // Check capacity

    if (capacity <= 0)
    {
        cout << "Invalid train capacity!"
             << endl;

        return;
    }


    // Check that all stations exist

    for (int station : stations)
    {
        if (station < 0 ||
            station >= city.getLocationCount())
        {
            cout << "Invalid train station!"
                 << endl;

            return;
        }
    }


    // Create train route

    TrainRoute route;

    route.trainNumber = trainNumber;

    route.routeName = routeName;

    route.stations = stations;

    route.capacity = capacity;

    route.currentPassengers = 0;

    route.startTime = startTime;

    route.endTime = endTime;


    // Add route to train network

    trainRoutes.push_back(route);


    // ======================================
    // ADD TRAIN CONNECTIONS TO GRAPH
    // ======================================

    for (int i = 0;
         i < stations.size() - 1;
         i++)
    {
        city.addBidirectionalConnection(
            stations[i],
            stations[i + 1],
            travelTime,
            "Train"
        );
    }
}


// ==========================================
// DISPLAY TRAIN ROUTES
// ==========================================

void TrainNetwork::displayTrainRoutes()
{
    cout << "\n===== TRAIN NETWORK =====\n";


    for (const TrainRoute& route :
         trainRoutes)
    {
        cout << "\nTrain Number: "
             << route.trainNumber;


        cout << "\nRoute: "
             << route.routeName;


        cout << "\nStation IDs: ";


        for (int station :
             route.stations)
        {
            cout << station << " ";
        }


        cout << "\nCapacity: "
             << route.capacity;


        cout << "\nCurrent Passengers: "
             << route.currentPassengers;


        cout << "\nOperating Time: "
             << route.startTime
             << " - "
             << route.endTime;


        cout << "\n";
    }
}


// ==========================================
// DISPLAY TRAIN ROUTES WITH STATION NAMES
// ==========================================

void TrainNetwork::displayTrainRoutes(
    const Graph& city
)
{
    cout << "\n===== TRAIN NETWORK =====\n";


    for (const TrainRoute& route :
         trainRoutes)
    {
        cout << "\nTrain Number: "
             << route.trainNumber;


        cout << "\nRoute: "
             << route.routeName;


        cout << "\nStations: ";


        for (int i = 0;
             i < route.stations.size();
             i++)
        {
            cout << city.getLocationName(
                route.stations[i]
            );


            if (i < route.stations.size() - 1)
            {
                cout << " -> ";
            }
        }


        cout << "\nCapacity: "
             << route.capacity;


        cout << "\nCurrent Passengers: "
             << route.currentPassengers;


        cout << "\nOperating Time: "
             << route.startTime
             << " - "
             << route.endTime;


        cout << "\n";
    }
}


// ==========================================
// GET TRAIN ROUTE COUNT
// ==========================================

int TrainNetwork::getTrainRouteCount()
{
    return trainRoutes.size();
}


// ==========================================
// GET TRAIN ROUTE
// ==========================================

TrainRoute TrainNetwork::getTrainRoute(
    int index
)
{
    if (index < 0 ||
        index >= trainRoutes.size())
    {
        return {};
    }


    return trainRoutes[index];
}


// ==========================================
// FIND TRAINS AT A STATION
// ==========================================

vector<int> TrainNetwork::findTrainsAtStation(
    int stationId
)
{
    vector<int> result;


    for (int i = 0;
         i < trainRoutes.size();
         i++)
    {
        if (isStationInRoute(
                i,
                stationId))
        {
            result.push_back(
                trainRoutes[i].trainNumber
            );
        }
    }


    return result;
}


// ==========================================
// CHECK STATION IN TRAIN ROUTE
// ==========================================

bool TrainNetwork::isStationInRoute(
    int trainIndex,
    int stationId
)
{
    if (trainIndex < 0 ||
        trainIndex >= trainRoutes.size())
    {
        return false;
    }


    for (int station :
         trainRoutes[trainIndex].stations)
    {
        if (station == stationId)
        {
            return true;
        }
    }


    return false;
}


// ==========================================
// CHECK DIRECT TRAIN ROUTE
// ==========================================

bool TrainNetwork::canTravelByTrain(
    int startStation,
    int destinationStation
)
{
    for (const TrainRoute& route :
         trainRoutes)
    {
        bool startFound = false;


        for (int station :
             route.stations)
        {
            if (station == startStation)
            {
                startFound = true;
            }


            if (startFound &&
                station == destinationStation)
            {
                return true;
            }
        }
    }


    return false;
}


// ==========================================
// DISPLAY TRAINS AT STATION
// ==========================================

void TrainNetwork::displayTrainsAtStation(
    int stationId
)
{
    vector<int> trains =
        findTrainsAtStation(stationId);


    cout << "\nTrains available at station "
         << stationId
         << ": ";


    if (trains.empty())
    {
        cout << "No trains found."
             << endl;

        return;
    }


    for (int trainNumber :
         trains)
    {
        cout << trainNumber
             << " ";
    }


    cout << endl;
}


// ==========================================
// CHECK TRAIN OPERATING TIME
// ==========================================

bool TrainNetwork::isTrainOperating(
    int trainIndex,
    string currentTime
)
{
    if (trainIndex < 0 ||
        trainIndex >= trainRoutes.size())
    {
        return false;
    }


    string startTime =
        trainRoutes[trainIndex].startTime;


    string endTime =
        trainRoutes[trainIndex].endTime;


    if (currentTime >= startTime &&
        currentTime <= endTime)
    {
        return true;
    }


    return false;
}


// ==========================================
// BOARD PASSENGERS
// ==========================================

bool TrainNetwork::boardPassengers(
    int trainIndex,
    int passengerCount
)
{
    if (trainIndex < 0 ||
        trainIndex >= trainRoutes.size())
    {
        return false;
    }


    if (passengerCount <= 0)
    {
        return false;
    }


    int availableCapacity =
        trainRoutes[trainIndex].capacity
        -
        trainRoutes[trainIndex].currentPassengers;


    if (passengerCount >
        availableCapacity)
    {
        return false;
    }


    trainRoutes[trainIndex].currentPassengers +=
        passengerCount;


    return true;
}


// ==========================================
// PASSENGERS LEAVE TRAIN
// ==========================================

bool TrainNetwork::leavePassengers(
    int trainIndex,
    int passengerCount
)
{
    if (trainIndex < 0 ||
        trainIndex >= trainRoutes.size())
    {
        return false;
    }


    if (passengerCount <= 0)
    {
        return false;
    }


    if (passengerCount >
        trainRoutes[trainIndex].currentPassengers)
    {
        return false;
    }


    trainRoutes[trainIndex].currentPassengers -=
        passengerCount;


    return true;
}


// ==========================================
// GET AVAILABLE CAPACITY
// ==========================================

int TrainNetwork::getAvailableCapacity(
    int trainIndex
)
{
    if (trainIndex < 0 ||
        trainIndex >= trainRoutes.size())
    {
        return 0;
    }


    return trainRoutes[trainIndex].capacity
           -
           trainRoutes[trainIndex].currentPassengers;
}


// ==========================================
// DISPLAY TRAIN STATUS
// ==========================================

void TrainNetwork::displayTrainStatus()
{
    cout << "\n===== TRAIN STATUS =====\n";


    for (const TrainRoute& route :
         trainRoutes)
    {
        int available =
            route.capacity
            -
            route.currentPassengers;


        cout << "\nTrain Number: "
             << route.trainNumber;


        cout << "\nPassengers: "
             << route.currentPassengers
             << " / "
             << route.capacity;


        cout << "\nAvailable Seats: "
             << available;


        cout << "\n";
    }
}


// ==========================================
// BFS ROUTE FINDING
// ==========================================

void TrainNetwork::findRouteBFS(
    Graph& city,
    int start,
    int destination
)
{
    cout << "\n===== BFS ROUTE FINDING =====\n";


    int locationCount =
        city.getLocationCount();


    // ======================================
    // VALIDATE LOCATIONS
    // ======================================

    if (start < 0 ||
        start >= locationCount ||
        destination < 0 ||
        destination >= locationCount)
    {
        cout << "Invalid start or destination."
             << endl;

        return;
    }


    // ======================================
    // SAME LOCATION
    // ======================================

    if (start == destination)
    {
        cout << "You are already at "
             << city.getLocationName(start)
             << "." << endl;

        return;
    }


    // ======================================
    // BFS DATA STRUCTURES
    // ======================================

    vector<bool> visited(
        locationCount,
        false
    );


    vector<int> parent(
        locationCount,
        -1
    );


    queue<int> q;


    // ======================================
    // START BFS
    // ======================================

    visited[start] = true;

    q.push(start);


    // ======================================
    // BFS SEARCH
    // ======================================

    while (!q.empty())
    {
        int current =
            q.front();

        q.pop();


        vector<Edge> edges =
            city.getEdges(current);


        for (const Edge& edge :
             edges)
        {
            int next =
                edge.destination;


            if (!visited[next])
            {
                visited[next] = true;

                parent[next] = current;

                q.push(next);


                if (next == destination)
                {
                    break;
                }
            }
        }


        if (visited[destination])
        {
            break;
        }
    }


    // ======================================
    // NO ROUTE
    // ======================================

    if (!visited[destination])
    {
        cout << "No route found."
             << endl;

        return;
    }


    // ======================================
    // RECONSTRUCT ROUTE
    // ======================================

    vector<int> path;


    int current =
        destination;


    while (current != -1)
    {
        path.push_back(current);

        current =
            parent[current];
    }


    reverse(
        path.begin(),
        path.end()
    );


    // ======================================
    // DISPLAY BFS ROUTE
    // ======================================

    cout << "BFS Route: ";


    for (int i = 0;
         i < path.size();
         i++)
    {
        cout << city.getLocationName(
            path[i]
        );


        if (i < path.size() - 1)
        {
            cout << " -> ";
        }
    }


    cout << endl;


    cout << "Number of connections: "
         << path.size() - 1
         << endl;
}

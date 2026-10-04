#include "PassengerSimulation.h"

#include <queue>
#include <algorithm>


// ==========================================
// CONSTRUCTOR
// ==========================================

PassengerSimulation::PassengerSimulation()
{
    nextPassengerId = 1;

    completedPassengers = 0;

    waitingPassengers = 0;

    unablePassengers = 0;
}


// ==========================================
// ADD PASSENGER
// ==========================================

void PassengerSimulation::addPassenger(
    int origin,
    int destination,
    string demandTime
)
{
    Passenger passenger;

    passenger.passengerId =
        nextPassengerId++;

    passenger.origin =
        origin;

    passenger.destination =
        destination;

    passenger.demandTime =
        demandTime;

    passenger.currentLocation =
        origin;

    passenger.status =
        PassengerStatus::WAITING;

    passenger.transfers = 0;

    passenger.travelTime = 0;

    passengers.push_back(
        passenger
    );
}


// ==========================================
// GENERATE VARIABLE DEMAND
// ==========================================

void PassengerSimulation::generateDemand(
    Graph& city,
    string demandTime,
    int passengerCount
)
{
    if (city.getLocationCount() < 2)
    {
        return;
    }

    if (passengerCount <= 0)
    {
        return;
    }


    int locationCount =
        city.getLocationCount();


    for (int i = 0;
         i < passengerCount;
         i++)
    {
        int origin =
            i % locationCount;


        int destination =
            (i + 2) % locationCount;


        // Make sure origin and
        // destination are different

        if (origin == destination)
        {
            destination =
                (destination + 1)
                % locationCount;
        }


        addPassenger(
            origin,
            destination,
            demandTime
        );
    }


    cout << passengerCount
         << " passengers generated for "
         << demandTime
         << "."
         << endl;
}


// ==========================================
// DISPLAY PASSENGERS
// ==========================================

void PassengerSimulation::displayPassengers(
    const Graph& city
)
{
    cout << "\n===== PASSENGER LIST =====\n";


    if (passengers.empty())
    {
        cout << "No passengers available."
             << endl;

        return;
    }


    for (const Passenger& passenger :
         passengers)
    {
        cout << "\nPassenger ID: "
             << passenger.passengerId;


        cout << "\nOrigin: "
             << city.getLocationName(
                    passenger.origin
                );


        cout << "\nDestination: "
             << city.getLocationName(
                    passenger.destination
                );


        cout << "\nDemand Time: "
             << passenger.demandTime;


        cout << "\nCurrent Location: "
             << city.getLocationName(
                    passenger.currentLocation
                );


        cout << "\nTransfers: "
             << passenger.transfers;


        cout << "\nTravel Time: "
             << passenger.travelTime
             << " minutes";


        cout << "\nStatus: ";


        if (passenger.status ==
            PassengerStatus::WAITING)
        {
            cout << "WAITING";
        }
        else if (
            passenger.status ==
            PassengerStatus::TRAVELLING)
        {
            cout << "TRAVELLING";
        }
        else if (
            passenger.status ==
            PassengerStatus::COMPLETED)
        {
            cout << "COMPLETED";
        }
        else
        {
            cout << "UNABLE";
        }


        cout << "\n";
    }
}


// ==========================================
// DEMAND STATISTICS
// ==========================================

void PassengerSimulation::displayDemandStatistics()
{
    int morning = 0;

    int afternoon = 0;

    int evening = 0;


    for (const Passenger& passenger :
         passengers)
    {
        if (passenger.demandTime ==
            "Morning")
        {
            morning++;
        }
        else if (
            passenger.demandTime ==
            "Afternoon")
        {
            afternoon++;
        }
        else if (
            passenger.demandTime ==
            "Evening")
        {
            evening++;
        }
    }


    cout << "\n===== PASSENGER DEMAND =====\n";


    cout << "Morning Demand: "
         << morning
         << endl;


    cout << "Afternoon Demand: "
         << afternoon
         << endl;


    cout << "Evening Demand: "
         << evening
         << endl;


    cout << "Total Demand: "
         << passengers.size()
         << endl;
}


// ==========================================
// BFS ROUTE FINDING
// ==========================================

vector<int> PassengerSimulation::findRouteBFS(
    Graph& city,
    int start,
    int destination
)
{
    vector<int> emptyPath;


    int locationCount =
        city.getLocationCount();


    if (start < 0 ||
        start >= locationCount ||
        destination < 0 ||
        destination >= locationCount)
    {
        return emptyPath;
    }


    if (start == destination)
    {
        return {start};
    }


    vector<bool> visited(
        locationCount,
        false
    );


    vector<int> parent(
        locationCount,
        -1
    );


    queue<int> q;


    visited[start] = true;

    q.push(start);


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

                parent[next] =
                    current;

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


    if (!visited[destination])
    {
        return emptyPath;
    }


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


    return path;
}


// ==========================================
// FIND BUS FOR CONNECTION
// ==========================================

int PassengerSimulation::findBusForConnection(
    BusNetwork& busNetwork,
    int from,
    int to
)
{
    int routeCount =
        busNetwork.getBusRouteCount();


    for (int i = 0;
         i < routeCount;
         i++)
    {
        BusRoute route =
            busNetwork.getBusRoute(i);


        for (int j = 0;
             j + 1 < route.stops.size();
             j++)
        {
            if (
                (route.stops[j] == from &&
                 route.stops[j + 1] == to)
                ||
                (route.stops[j] == to &&
                 route.stops[j + 1] == from)
            )
            {
                return i;
            }
        }
    }


    return -1;
}


// ==========================================
// FIND TRAIN FOR CONNECTION
// ==========================================

int PassengerSimulation::findTrainForConnection(
    TrainNetwork& trainNetwork,
    int from,
    int to
)
{
    int routeCount =
        trainNetwork.getTrainRouteCount();


    for (int i = 0;
         i < routeCount;
         i++)
    {
        TrainRoute route =
            trainNetwork.getTrainRoute(i);


        for (int j = 0;
             j + 1 < route.stations.size();
             j++)
        {
            if (
                (route.stations[j] == from &&
                 route.stations[j + 1] == to)
                ||
                (route.stations[j] == to &&
                 route.stations[j + 1] == from)
            )
            {
                return i;
            }
        }
    }


    return -1;
}


// ==========================================
// SIMULATE ONE PASSENGER JOURNEY
// ==========================================

bool PassengerSimulation::simulatePassengerJourney(
    Passenger& passenger,
    Graph& city,
    BusNetwork& busNetwork,
    TrainNetwork& trainNetwork,
    string currentTime
)
{
    vector<int> path =
        findRouteBFS(
            city,
            passenger.origin,
            passenger.destination
        );


    if (path.empty())
    {
        passenger.status =
            PassengerStatus::UNABLE;

        return false;
    }


    passenger.status =
        PassengerStatus::TRAVELLING;


    passenger.currentLocation =
        passenger.origin;


    passenger.transfers = 0;

    passenger.travelTime = 0;


    string previousMode = "";


    // ======================================
    // TRAVEL THROUGH ROUTE
    // ======================================

    for (int i = 0;
         i + 1 < path.size();
         i++)
    {
        int from =
            path[i];

        int to =
            path[i + 1];


        vector<Edge> edges =
            city.getEdges(from);


        string transportMode = "";

        int travelTime = 0;


        // Find edge between locations

        for (const Edge& edge :
             edges)
        {
            if (edge.destination == to)
            {
                transportMode =
                    edge.transportMode;

                travelTime =
                    edge.travelTime;

                break;
            }
        }


        if (transportMode == "")
        {
            passenger.status =
                PassengerStatus::UNABLE;

            return false;
        }


        // ==================================
        // BUS
        // ==================================

        if (transportMode == "Bus")
        {
            int busIndex =
                findBusForConnection(
                    busNetwork,
                    from,
                    to
                );


            if (busIndex == -1)
            {
                passenger.status =
                    PassengerStatus::UNABLE;

                return false;
            }


            if (!busNetwork.isBusOperating(
                    busIndex,
                    currentTime))
            {
                passenger.status =
                    PassengerStatus::WAITING;

                return false;
            }


            if (!busNetwork.boardPassengers(
                    busIndex,
                    1))
            {
                passenger.status =
                    PassengerStatus::WAITING;

                return false;
            }


            cout << "Passenger "
                 << passenger.passengerId
                 << " boarded Bus "
                 << busNetwork.getBusRoute(
                        busIndex
                    ).busNumber
                 << "."
                 << endl;


            passenger.travelTime +=
                travelTime;


            busNetwork.leavePassengers(
                busIndex,
                1
            );


            passenger.currentLocation =
                to;
        }


        // ==================================
        // TRAIN
        // ==================================

        else if (
            transportMode == "Train")
        {
            int trainIndex =
                findTrainForConnection(
                    trainNetwork,
                    from,
                    to
                );


            if (trainIndex == -1)
            {
                passenger.status =
                    PassengerStatus::UNABLE;

                return false;
            }


            if (!trainNetwork.isTrainOperating(
                    trainIndex,
                    currentTime))
            {
                passenger.status =
                    PassengerStatus::WAITING;

                return false;
            }


            if (!trainNetwork.boardPassengers(
                    trainIndex,
                    1))
            {
                passenger.status =
                    PassengerStatus::WAITING;

                return false;
            }


            cout << "Passenger "
                 << passenger.passengerId
                 << " boarded Train "
                 << trainNetwork.getTrainRoute(
                        trainIndex
                    ).trainNumber
                 << "."
                 << endl;


            passenger.travelTime +=
                travelTime;


            trainNetwork.leavePassengers(
                trainIndex,
                1
            );


            passenger.currentLocation =
                to;
        }


        else
        {
            passenger.status =
                PassengerStatus::UNABLE;

            return false;
        }


        // ==================================
        // TRANSFER CHECK
        // ==================================

        if (previousMode != "" &&
            previousMode != transportMode)
        {
            passenger.transfers++;
        }


        previousMode =
            transportMode;
    }


    passenger.status =
        PassengerStatus::COMPLETED;


    return true;
}


// ==========================================
// SIMULATE ALL JOURNEYS
// ==========================================

void PassengerSimulation::simulateJourneys(
    Graph& city,
    BusNetwork& busNetwork,
    TrainNetwork& trainNetwork,
    string currentTime
)
{
    completedPassengers = 0;

    waitingPassengers = 0;

    unablePassengers = 0;


    cout << "\n===== PASSENGER JOURNEY SIMULATION =====\n";


    for (Passenger& passenger :
         passengers)
    {
        cout << "\nPassenger "
             << passenger.passengerId
             << ": "
             << city.getLocationName(
                    passenger.origin
                )
             << " -> "
             << city.getLocationName(
                    passenger.destination
                )
             << endl;


        bool completed =
            simulatePassengerJourney(
                passenger,
                city,
                busNetwork,
                trainNetwork,
                currentTime
            );


        if (completed)
        {
            completedPassengers++;

            cout << "Journey completed."
                 << endl;
        }
        else if (
            passenger.status ==
            PassengerStatus::WAITING)
        {
            waitingPassengers++;

            cout << "Passenger is waiting."
                 << endl;
        }
        else
        {
            unablePassengers++;

            cout << "Journey could not be completed."
                 << endl;
        }
    }
}


// ==========================================
// DISPLAY SIMULATION RESULTS
// ==========================================

void PassengerSimulation::displaySimulationResults()
{
    cout << "\n===== SIMULATION RESULTS =====\n";


    cout << "Total Passengers: "
         << passengers.size()
         << endl;


    cout << "Completed Journeys: "
         << completedPassengers
         << endl;


    cout << "Waiting Passengers: "
         << waitingPassengers
         << endl;


    cout << "Unable Journeys: "
         << unablePassengers
         << endl;


    if (!passengers.empty())
    {
        double completionRate =
            completedPassengers * 100.0
            /
            passengers.size();


        cout << "Completion Rate: "
             << completionRate
             << "%"
             << endl;
    }
}


// ==========================================
// GET PASSENGER COUNT
// ==========================================

int PassengerSimulation::getPassengerCount()
{
    return passengers.size();
}


// ==========================================
// GET COMPLETED PASSENGERS
// ==========================================

int PassengerSimulation::getCompletedPassengers()
{
    return completedPassengers;
}


// ==========================================
// GET WAITING PASSENGERS
// ==========================================

int PassengerSimulation::getWaitingPassengers()
{
    return waitingPassengers;
}


// ==========================================
// GET UNABLE PASSENGERS
// ==========================================

int PassengerSimulation::getUnablePassengers()
{
    return unablePassengers;
}

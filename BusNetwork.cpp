#include "BusNetwork.h"

void BusNetwork::addBusRoute(
    int busNumber,
    string routeName,
    vector<int> stops,
    int capacity,
    string startTime,
    string endTime
)
{
    BusRoute route;

    route.busNumber = busNumber;
    route.routeName = routeName;
    route.stops = stops;

    route.capacity = capacity;
    route.currentPassengers = 0;

    route.startTime = startTime;
    route.endTime = endTime;

    busRoutes.push_back(route);
}


// ==========================================
// DISPLAY BUS ROUTES
// ==========================================

void BusNetwork::displayBusRoutes()
{
    cout << "\n===== BUS NETWORK =====\n";

    for (const BusRoute& route :
         busRoutes)
    {
        cout << "\nBus Number: "
             << route.busNumber;

        cout << "\nRoute: "
             << route.routeName;

        cout << "\nStops: ";

        for (int stop :
             route.stops)
        {
            cout << stop << " ";
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
// DISPLAY BUS ROUTES WITH LOCATION NAMES
// ==========================================

void BusNetwork::displayBusRoutes(
    const Graph& city
)
{
    cout << "\n===== BUS NETWORK =====\n";

    for (const BusRoute& route :
         busRoutes)
    {
        cout << "\nBus Number: "
             << route.busNumber;

        cout << "\nRoute: "
             << route.routeName;

        cout << "\nStops: ";

        for (int i = 0;
             i < route.stops.size();
             i++)
        {
            cout << city.getLocationName(
                route.stops[i]
            );

            if (i < route.stops.size() - 1)
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
// GET BUS ROUTE COUNT
// ==========================================

int BusNetwork::getBusRouteCount()
{
    return busRoutes.size();
}


// ==========================================
// GET BUS ROUTE
// ==========================================

BusRoute BusNetwork::getBusRoute(
    int index
)
{
    if (index < 0 ||
        index >= busRoutes.size())
    {
        return {};
    }

    return busRoutes[index];
}


// ==========================================
// FIND BUSES AT A STOP
// ==========================================

vector<int> BusNetwork::findBusesAtStop(
    int stopId
)
{
    vector<int> result;

    for (int i = 0;
         i < busRoutes.size();
         i++)
    {
        if (isStopInRoute(
                i,
                stopId))
        {
            result.push_back(
                busRoutes[i].busNumber
            );
        }
    }

    return result;
}


// ==========================================
// CHECK STOP IN ROUTE
// ==========================================

bool BusNetwork::isStopInRoute(
    int busIndex,
    int stopId
)
{
    if (busIndex < 0 ||
        busIndex >= busRoutes.size())
    {
        return false;
    }

    for (int stop :
         busRoutes[busIndex].stops)
    {
        if (stop == stopId)
        {
            return true;
        }
    }

    return false;
}


// ==========================================
// CHECK BUS ROUTE
// ==========================================

bool BusNetwork::canTravelByBus(
    int startStop,
    int destinationStop
)
{
    for (const BusRoute& route :
         busRoutes)
    {
        bool startFound = false;

        for (int stop :
             route.stops)
        {
            if (stop == startStop)
            {
                startFound = true;
            }

            if (startFound &&
                stop == destinationStop)
            {
                return true;
            }
        }
    }

    return false;
}


// ==========================================
// DISPLAY BUSES AT A STOP
// ==========================================

void BusNetwork::displayBusesAtStop(
    int stopId
)
{
    vector<int> buses =
        findBusesAtStop(stopId);

    cout << "\nBuses available at stop "
         << stopId
         << ": ";

    if (buses.empty())
    {
        cout << "No buses found."
             << endl;

        return;
    }

    for (int busNumber :
         buses)
    {
        cout << busNumber
             << " ";
    }

    cout << endl;
}


// ==========================================
// CHECK BUS OPERATING TIME
// ==========================================

bool BusNetwork::isBusOperating(
    int busIndex,
    string currentTime
)
{
    if (busIndex < 0 ||
        busIndex >= busRoutes.size())
    {
        return false;
    }

    string startTime =
        busRoutes[busIndex].startTime;

    string endTime =
        busRoutes[busIndex].endTime;

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

bool BusNetwork::boardPassengers(
    int busIndex,
    int passengerCount
)
{
    if (busIndex < 0 ||
        busIndex >= busRoutes.size())
    {
        return false;
    }

    if (passengerCount <= 0)
    {
        return false;
    }

    int availableCapacity =
        busRoutes[busIndex].capacity -
        busRoutes[busIndex].currentPassengers;

    if (passengerCount >
        availableCapacity)
    {
        return false;
    }

    busRoutes[busIndex].currentPassengers +=
        passengerCount;

    return true;
}


// ==========================================
// PASSENGERS LEAVE BUS
// ==========================================

bool BusNetwork::leavePassengers(
    int busIndex,
    int passengerCount
)
{
    if (busIndex < 0 ||
        busIndex >= busRoutes.size())
    {
        return false;
    }

    if (passengerCount <= 0)
    {
        return false;
    }

    if (passengerCount >
        busRoutes[busIndex].currentPassengers)
    {
        return false;
    }

    busRoutes[busIndex].currentPassengers -=
        passengerCount;

    return true;
}


// ==========================================
// GET AVAILABLE CAPACITY
// ==========================================

int BusNetwork::getAvailableCapacity(
    int busIndex
)
{
    if (busIndex < 0 ||
        busIndex >= busRoutes.size())
    {
        return 0;
    }

    return busRoutes[busIndex].capacity -
           busRoutes[busIndex].currentPassengers;
}


// ==========================================
// DISPLAY BUS STATUS
// ==========================================

void BusNetwork::displayBusStatus()
{
    cout << "\n===== BUS STATUS =====\n";

    for (const BusRoute& route :
         busRoutes)
    {
        int available =
            route.capacity -
            route.currentPassengers;

        cout << "\nBus Number: "
             << route.busNumber;

        cout << "\nPassengers: "
             << route.currentPassengers
             << " / "
             << route.capacity;

        cout << "\nAvailable Seats: "
             << available;

        cout << "\n";
    }
}
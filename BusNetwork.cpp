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
    route.startTime = startTime;
    route.endTime = endTime;

    busRoutes.push_back(route);
}

void BusNetwork::displayBusRoutes()
{
    cout << "\n===== BUS NETWORK =====\n";

    for (const BusRoute& route : busRoutes)
    {
        cout << "\nBus Number: "
             << route.busNumber;

        cout << "\nRoute: "
             << route.routeName;

        cout << "\nStops: ";

        for (int stop : route.stops)
        {
            cout << stop << " ";
        }

        cout << "\nCapacity: "
             << route.capacity;

        cout << "\nOperating Time: "
             << route.startTime
             << " - "
             << route.endTime;

        cout << "\n";
    }
}

int BusNetwork::getBusRouteCount()
{
    return busRoutes.size();
}

BusRoute BusNetwork::getBusRoute(int index)
{
    return busRoutes[index];
}

vector<int> BusNetwork::findBusesAtStop(int stopId)
{
    vector<int> result;

    for (int i = 0; i < busRoutes.size(); i++)
    {
        if (isStopInRoute(i, stopId))
        {
            result.push_back(
                busRoutes[i].busNumber
            );
        }
    }

    return result;
}

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

    for (int stop : busRoutes[busIndex].stops)
    {
        if (stop == stopId)
        {
            return true;
        }
    }

    return false;
}

bool BusNetwork::canTravelByBus(
    int startStop,
    int destinationStop
)
{
    for (const BusRoute& route : busRoutes)
    {
        bool startFound = false;

        for (int stop : route.stops)
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

void BusNetwork::displayBusesAtStop(int stopId)
{
    vector<int> buses =
        findBusesAtStop(stopId);

    cout << "\nBuses available at stop "
         << stopId << ": ";

    if (buses.empty())
    {
        cout << "No buses found."
             << endl;

        return;
    }

    for (int busNumber : buses)
    {
        cout << busNumber << " ";
    }

    cout << endl;
}
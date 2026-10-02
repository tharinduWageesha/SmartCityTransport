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
        cout << "\nBus Number: " << route.busNumber;
        cout << "\nRoute: " << route.routeName;

        cout << "\nStops: ";

        for (int stop : route.stops)
        {
            cout << stop << " ";
        }

        cout << "\nCapacity: " << route.capacity;
        cout << "\nOperating Time: "
             << route.startTime << " - "
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
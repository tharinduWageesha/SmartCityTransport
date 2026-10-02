#ifndef BUSNETWORK_H
#define BUSNETWORK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct BusRoute
{
    int busNumber;
    string routeName;
    vector<int> stops;

    int capacity;
    int currentPassengers;

    string startTime;
    string endTime;
};

class BusNetwork
{
private:
    vector<BusRoute> busRoutes;

public:
    void addBusRoute(
        int busNumber,
        string routeName,
        vector<int> stops,
        int capacity,
        string startTime,
        string endTime
    );

    void displayBusRoutes();

    int getBusRouteCount();

    BusRoute getBusRoute(int index);

    vector<int> findBusesAtStop(int stopId);

    bool isStopInRoute(
        int busIndex,
        int stopId
    );

    bool canTravelByBus(
        int startStop,
        int destinationStop
    );

    void displayBusesAtStop(int stopId);

    bool isBusOperating(
        int busIndex,
        string currentTime
    );

    bool boardPassengers(
        int busIndex,
        int passengerCount
    );

    bool leavePassengers(
        int busIndex,
        int passengerCount
    );

    int getAvailableCapacity(
        int busIndex
    );

    void displayBusStatus();
};

#endif
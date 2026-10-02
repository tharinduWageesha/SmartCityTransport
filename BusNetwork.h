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
};

#endif
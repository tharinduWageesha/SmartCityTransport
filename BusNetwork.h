#ifndef BUSNETWORK_H
#define BUSNETWORK_H

#include <iostream>
#include <vector>
#include <string>

#include "Graph.h"

struct RouteInfo
{
    std::string routeId;
    std::string routeName;
    Mode mode;
    std::vector<int> stationSequence;
    int frequencyMin;
    int capacityPerVehicle;
};

class BusNetwork
{
private:
    std::vector<RouteInfo> busRoutes;

public:
    BusNetwork();

    void registerBusRoute(Graph& city, const RouteInfo& route);

    const std::vector<RouteInfo>& getBusRoutes() const;

    void displayBusNetwork(const Graph& city) const;
};

#endif

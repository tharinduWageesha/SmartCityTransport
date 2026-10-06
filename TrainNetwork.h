#ifndef TRAINNETWORK_H
#define TRAINNETWORK_H

#include <iostream>
#include <vector>
#include <string>

#include "Graph.h"
#include "BusNetwork.h"

class TrainNetwork
{
private:
    std::vector<RouteInfo> trainRoutes;

public:
    TrainNetwork();

    void registerTrainRoute(Graph& city, const RouteInfo& route);

    const std::vector<RouteInfo>& getTrainRoutes() const;

    void displayTrainNetwork(const Graph& city) const;
};

#endif

#include "TrainNetwork.h"

TrainNetwork::TrainNetwork()
{
}

void TrainNetwork::registerTrainRoute(Graph& city, const RouteInfo& route)
{
    trainRoutes.push_back(route);
    for (size_t i = 0; i + 1 < route.stationSequence.size(); ++i)
    {
        int u = route.stationSequence[i];
        int v = route.stationSequence[i + 1];
        city.addUndirectedEdge(u, v, Mode::TRAIN, route.routeName, 5, 5.0);
    }
}

const std::vector<RouteInfo>& TrainNetwork::getTrainRoutes() const
{
    return trainRoutes;
}

void TrainNetwork::displayTrainNetwork(const Graph& city) const
{
    std::cout << "\n===============================================================================\n";
    std::cout << "  TRAIN NETWORK & TRAIN ROUTES\n";
    std::cout << "===============================================================================\n";
    std::cout << "  High-capacity rail links cross-district hubs with zero street traffic.\n\n";

    for (const auto& route : trainRoutes)
    {
        std::cout << "  [" << route.routeId << "] " << route.routeName << "\n";
        std::cout << "    Time: " << route.frequencyMin << " mins\n\n";
    }
}

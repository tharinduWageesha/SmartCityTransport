#include "BusNetwork.h"

BusNetwork::BusNetwork()
{
}

void BusNetwork::registerBusRoute(Graph& city, const RouteInfo& route)
{
    busRoutes.push_back(route);
    for (size_t i = 0; i + 1 < route.stationSequence.size(); ++i)
    {
        int u = route.stationSequence[i];
        int v = route.stationSequence[i + 1];
        city.addUndirectedEdge(u, v, Mode::BUS, route.routeName, 4, 1.5);
    }
}

const std::vector<RouteInfo>& BusNetwork::getBusRoutes() const
{
    return busRoutes;
}

void BusNetwork::displayBusNetwork(const Graph& city) const
{
    std::cout << "\n===============================================================================\n";
    std::cout << "  BUS NETWORK & BUS ROUTES\n";
    std::cout << "===============================================================================\n";
    std::cout << "  Buses provide local last-mile connectivity and feed into intermodal hubs.\n\n";

    for (const auto& route : busRoutes)
    {
        std::cout << "  [" << route.routeId << "] " << route.routeName << "\n";
        std::cout << "    Headway: " << route.frequencyMin << " mins | Capacity/Bus: " 
                  << route.capacityPerVehicle << " pax\n";
        std::cout << "    Route Itinerary: ";
        for (size_t i = 0; i < route.stationSequence.size(); ++i)
        {
            std::cout << city.getStation(route.stationSequence[i]).name;
            if (i + 1 < route.stationSequence.size()) std::cout << " <---> ";
        }
        std::cout << "\n\n";
    }
}

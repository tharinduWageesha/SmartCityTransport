#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

#include "Passenger.h"

struct Edge
{
    int to;
    Mode mode;
    std::string routeName;
    int travelTimeMin;
    double distanceKm;
};

struct Station
{
    int id;
    std::string name;
    std::string zone;
    StationType type;
};

class Graph
{
private:
    std::vector<Station> stations;
    std::unordered_map<std::string, int> stationNameToId;
    std::vector<std::vector<Edge>> adj;

public:
    Graph();

    int addStation(const std::string& name, const std::string& zone, StationType type);

    void addDirectEdge(int u, int v, Mode mode, const std::string& routeName, int timeMin, double distKm);

    void addUndirectedEdge(int u, int v, Mode mode, const std::string& routeName, int timeMin, double distKm);

    int getStationCount() const;
    int getEdgeCount() const;

    const Station& getStation(int id) const;
    int getStationId(const std::string& name) const;
    const std::vector<Station>& getAllStations() const;
    const std::vector<Edge>& getNeighbors(int u) const;

    void displayLocations() const;

    Itinerary findPathBFS(int startNode, int targetNode, Mode allowedMode = Mode::WALK_TRANSFER) const;

    Itinerary findMultiModalJourneyBFS(int startNode, int transferHub, int destNode, Mode mode1, Mode mode2) const;

    Itinerary findSmartIntermodalRouteBFS(int startNode, int destNode) const;
};

#endif

#include "Graph.h"
#include <iomanip>

std::string modeToString(Mode m)
{
    switch (m)
    {
        case Mode::TRAIN: return "TRAIN";
        case Mode::BUS:   return "BUS";
        case Mode::WALK_TRANSFER: return "TRANSFER";
        default: return "UNKNOWN";
    }
}

std::string modeTag(Mode m)
{
    switch (m)
    {
        case Mode::TRAIN: return "[TRAIN]";
        case Mode::BUS:   return "[BUS]";
        case Mode::WALK_TRANSFER: return "[XFER]";
        default: return "[???]";
    }
}

std::string stationTypeToString(StationType st)
{
    switch (st)
    {
        case StationType::BUS_STOP_ONLY: return "Bus Stop";
        case StationType::TRAIN_STATION_ONLY: return "Train Station";
        case StationType::INTERMODAL_HUB: return "Intermodal Hub (Train + Bus)";
        default: return "Standard";
    }
}

std::string timeOfDayToString(TimeOfDay t)
{
    switch (t)
    {
        case TimeOfDay::MORNING_PEAK:   return "Morning Peak (06:30 - 09:30)";
        case TimeOfDay::MIDDAY_OFFPEAK: return "Midday Off-Peak (10:00 - 15:30)";
        case TimeOfDay::EVENING_PEAK:   return "Evening Peak (16:30 - 19:30)";
        case TimeOfDay::NIGHT_HOURS:     return "Night Low-Demand (21:00 - 05:00)";
        default: return "General";
    }
}

Graph::Graph()
{
}

int Graph::addStation(const std::string& name, const std::string& zone, StationType type)
{
    int id = static_cast<int>(stations.size());
    stations.push_back({id, name, zone, type});
    stationNameToId[name] = id;
    adj.emplace_back();
    return id;
}

void Graph::addDirectEdge(int u, int v, Mode mode, const std::string& routeName, int timeMin, double distKm)
{
    if (u >= 0 && u < static_cast<int>(adj.size()) && v >= 0 && v < static_cast<int>(adj.size()))
    {
        adj[u].push_back({v, mode, routeName, timeMin, distKm});
    }
}

void Graph::addUndirectedEdge(int u, int v, Mode mode, const std::string& routeName, int timeMin, double distKm)
{
    addDirectEdge(u, v, mode, routeName, timeMin, distKm);
    addDirectEdge(v, u, mode, routeName, timeMin, distKm);
}

int Graph::getStationCount() const
{
    return static_cast<int>(stations.size());
}

int Graph::getEdgeCount() const
{
    int count = 0;
    for (const auto& list : adj)
    {
        count += static_cast<int>(list.size());
    }
    return count / 2;
}

const Station& Graph::getStation(int id) const
{
    return stations[id];
}

int Graph::getStationId(const std::string& name) const
{
    auto it = stationNameToId.find(name);
    if (it != stationNameToId.end())
    {
        return it->second;
    }
    return -1;
}

const std::vector<Station>& Graph::getAllStations() const
{
    return stations;
}

const std::vector<Edge>& Graph::getNeighbors(int u) const
{
    return adj[u];
}

void Graph::displayLocations() const
{
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "  CITY LOCATIONS & HUBS (|V| = " << getStationCount() << ")\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << std::left << std::setw(4) << "ID"
              << std::setw(20) << "Location Name"
              << std::setw(20) << "Zone"
              << "Classification\n";
    std::cout << "--------------------------------------------------\n";

    for (const auto& s : stations)
    {
        std::cout << std::left << std::setw(4) << s.id
                  << std::setw(20) << s.name
                  << std::setw(20) << s.zone
                  << stationTypeToString(s.type) << "\n";
    }
    std::cout << "--------------------------------------------------\n";
    std::cout << "Total Locations (V): " << getStationCount() 
              << " | Total Network Links (E): " << getEdgeCount() << "\n";
}

Itinerary Graph::findPathBFS(int startNode, int targetNode, Mode allowedMode) const
{
    Itinerary itin;
    itin.origin = startNode;
    itin.destination = targetNode;

    if (startNode < 0 || startNode >= getStationCount() ||
        targetNode < 0 || targetNode >= getStationCount())
    {
        return itin;
    }

    if (startNode == targetNode)
    {
        itin.found = true;
        return itin;
    }

    std::vector<bool> visited(getStationCount(), false);
    std::vector<int> parentStation(getStationCount(), -1);
    std::vector<Edge> parentEdge(getStationCount());

    std::queue<int> q;
    visited[startNode] = true;
    q.push(startNode);

    bool reached = false;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        if (curr == targetNode)
        {
            reached = true;
            break;
        }

        for (const auto& edge : adj[curr])
        {
            if (allowedMode != Mode::WALK_TRANSFER && edge.mode != allowedMode)
            {
                continue;
            }

            if (!visited[edge.to])
            {
                visited[edge.to] = true;
                parentStation[edge.to] = curr;
                parentEdge[edge.to] = edge;
                q.push(edge.to);
            }
        }
    }

    if (!reached)
    {
        itin.found = false;
        return itin;
    }

    std::vector<TripStep> reversedSteps;
    int curr = targetNode;
    while (curr != startNode)
    {
        int p = parentStation[curr];
        const Edge& e = parentEdge[curr];
        reversedSteps.push_back({p, curr, e.mode, e.routeName, e.travelTimeMin, e.distanceKm});
        curr = p;
    }

    std::reverse(reversedSteps.begin(), reversedSteps.end());
    itin.steps = reversedSteps;
    itin.found = true;

    Mode prevMode = Mode::WALK_TRANSFER;
    std::string prevRoute = "";
    for (size_t i = 0; i < itin.steps.size(); ++i)
    {
        const auto& step = itin.steps[i];
        itin.totalTimeMin += step.timeMin;
        itin.totalDistKm += step.distKm;
        if (step.mode == Mode::BUS) itin.busLegs++;
        if (step.mode == Mode::TRAIN) itin.trainLegs++;

        if (i > 0 && (step.mode != prevMode || step.routeName != prevRoute))
        {
            itin.transfers++;
            itin.totalTimeMin += 3;
        }
        prevMode = step.mode;
        prevRoute = step.routeName;
    }

    return itin;
}

Itinerary Graph::findMultiModalJourneyBFS(int startNode, int transferHub, int destNode, Mode mode1, Mode mode2) const
{
    Itinerary part1 = findPathBFS(startNode, transferHub, mode1);
    Itinerary part2 = findPathBFS(transferHub, destNode, mode2);

    Itinerary combined;
    combined.origin = startNode;
    combined.destination = destNode;

    if (!part1.found || !part2.found)
    {
        combined.found = false;
        return combined;
    }

    combined.found = true;
    combined.steps = part1.steps;
    for (const auto& step : part2.steps)
    {
        combined.steps.push_back(step);
    }

    combined.totalTimeMin = part1.totalTimeMin + part2.totalTimeMin + 5;
    combined.totalDistKm = part1.totalDistKm + part2.totalDistKm;
    combined.transfers = part1.transfers + part2.transfers + 1;
    combined.busLegs = part1.busLegs + part2.busLegs;
    combined.trainLegs = part1.trainLegs + part2.trainLegs;

    return combined;
}

Itinerary Graph::findSmartIntermodalRouteBFS(int startNode, int destNode) const
{
    return findPathBFS(startNode, destNode);
}

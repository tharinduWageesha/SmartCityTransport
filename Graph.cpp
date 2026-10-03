#include "Graph.h"

int Graph::addLocation(string name)
{
    int id = locations.size();

    locations.push_back({id, name});
    adjacencyList.push_back({});

    return id;
}

void Graph::addConnection(
    int from,
    int to,
    int travelTime,
    string transportMode
)
{
    if (from < 0 || from >= locations.size() ||
        to < 0 || to >= locations.size() ||
        travelTime <= 0)
    {
        cout << "Invalid connection!" << endl;
        return;
    }

    adjacencyList[from].push_back(
        {to, travelTime, transportMode}
    );
}

void Graph::addBidirectionalConnection(
    int from,
    int to,
    int travelTime,
    string transportMode
)
{
    addConnection(
        from,
        to,
        travelTime,
        transportMode
    );

    addConnection(
        to,
        from,
        travelTime,
        transportMode
    );
}

void Graph::displayLocations()
{
    cout << "\n--- City Locations ---\n";

    for (const Location& location : locations)
    {
        cout << location.id
             << " - "
             << location.name
             << endl;
    }
}

void Graph::displayConnections()
{
    cout << "\n--- Transportation Connections ---\n";

    for (int i = 0;
         i < adjacencyList.size();
         i++)
    {
        cout << locations[i].name
             << " -> ";

        for (const Edge& edge :
             adjacencyList[i])
        {
            cout << locations[edge.destination].name
                 << " ["
                 << edge.transportMode
                 << ", "
                 << edge.travelTime
                 << " min] ";
        }

        cout << endl;
    }
}

int Graph::getLocationCount() const
{
    return locations.size();
}

string Graph::getLocationName(int id) const
{
    if (id < 0 || id >= locations.size())
    {
        return "Unknown";
    }

    return locations[id].name;
}

vector<Edge> Graph::getEdges(int id) const
{
    if (id < 0 ||
        id >= adjacencyList.size())
    {
        return {};
    }

    return adjacencyList[id];
}
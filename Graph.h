#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Edge
{
    int destination;
    int travelTime;
    string transportMode;
};

struct Location
{
    int id;
    string name;
};

class Graph
{
private:
    vector<Location> locations;
    vector<vector<Edge>> adjacencyList;

public:
    int addLocation(string name);

    void addConnection(
        int from,
        int to,
        int travelTime,
        string transportMode
    );

    void addBidirectionalConnection(
        int from,
        int to,
        int travelTime,
        string transportMode
    );

    void displayLocations();
    void displayConnections();

    int getLocationCount() const;
    string getLocationName(int id) const;
    vector<Edge> getEdges(int id) const;
};

#endif
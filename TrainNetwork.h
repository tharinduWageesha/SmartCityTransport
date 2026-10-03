#ifndef TRAINNETWORK_H
#define TRAINNETWORK_H

#include <iostream>
#include <vector>
#include <string>

#include "Graph.h"

using namespace std;


// ==========================================
// TRAIN ROUTE STRUCTURE
// ==========================================

struct TrainRoute
{
    int trainNumber;
    string routeName;

    vector<int> stations;

    int capacity;
    int currentPassengers;

    string startTime;
    string endTime;
};


// ==========================================
// TRAIN NETWORK CLASS
// ==========================================

class TrainNetwork
{
private:

    vector<TrainRoute> trainRoutes;


public:

    // ======================================
    // TRAIN ROUTE MANAGEMENT
    // ======================================

    void addTrainRoute(
        Graph& city,
        int trainNumber,
        string routeName,
        vector<int> stations,
        int travelTime,
        int capacity,
        string startTime,
        string endTime
    );


    void displayTrainRoutes();


    void displayTrainRoutes(
        const Graph& city
    );


    int getTrainRouteCount();


    TrainRoute getTrainRoute(
        int index
    );


    // ======================================
    // TRAIN STATION SEARCH
    // ======================================

    vector<int> findTrainsAtStation(
        int stationId
    );


    bool isStationInRoute(
        int trainIndex,
        int stationId
    );


    bool canTravelByTrain(
        int startStation,
        int destinationStation
    );


    void displayTrainsAtStation(
        int stationId
    );


    // ======================================
    // TRAIN SCHEDULE
    // ======================================

    bool isTrainOperating(
        int trainIndex,
        string currentTime
    );


    // ======================================
    // PASSENGER MANAGEMENT
    // ======================================

    bool boardPassengers(
        int trainIndex,
        int passengerCount
    );


    bool leavePassengers(
        int trainIndex,
        int passengerCount
    );


    int getAvailableCapacity(
        int trainIndex
    );


    void displayTrainStatus();


    // ======================================
    // BFS ROUTE FINDING
    // ======================================

    void findRouteBFS(
        Graph& city,
        int start,
        int destination
    );


    // ======================================
    // DIJKSTRA ROUTE FINDING
    // ======================================

    void findShortestTravelTimeDijkstra(
        Graph& city,
        int start,
        int destination
    );
};

#endif

#ifndef PASSENGERSIMULATION_H
#define PASSENGERSIMULATION_H

#include <iostream>
#include <vector>
#include <string>

#include "Graph.h"
#include "BusNetwork.h"
#include "TrainNetwork.h"
#include "Passenger.h"

using namespace std;

class PassengerSimulation
{
private:

    vector<Passenger> passengers;

    int nextPassengerId;

    int completedPassengers;
    int waitingPassengers;
    int unablePassengers;

public:

    PassengerSimulation();


    // ======================================
    // PASSENGER MANAGEMENT
    // ======================================

    void addPassenger(
        int origin,
        int destination,
        string demandTime
    );


    // ======================================
    // DEMAND GENERATION
    // ======================================

    void generateDemand(
        Graph& city,
        string demandTime,
        int passengerCount
    );


    // ======================================
    // DISPLAY PASSENGERS
    // ======================================

    void displayPassengers(
        const Graph& city
    );


    // ======================================
    // DEMAND STATISTICS
    // ======================================

    void displayDemandStatistics();


    // ======================================
    // JOURNEY SIMULATION
    // ======================================

    void simulateJourneys(
        Graph& city,
        BusNetwork& busNetwork,
        TrainNetwork& trainNetwork,
        string currentTime
    );


    // ======================================
    // INDIVIDUAL JOURNEY
    // ======================================

    bool simulatePassengerJourney(
        Passenger& passenger,
        Graph& city,
        BusNetwork& busNetwork,
        TrainNetwork& trainNetwork,
        string currentTime
    );


    // ======================================
    // BFS ROUTE
    // ======================================

    vector<int> findRouteBFS(
        Graph& city,
        int start,
        int destination
    );


    // ======================================
    // FIND BUS
    // ======================================

    int findBusForConnection(
        BusNetwork& busNetwork,
        int from,
        int to
    );


    // ======================================
    // FIND TRAIN
    // ======================================

    int findTrainForConnection(
        TrainNetwork& trainNetwork,
        int from,
        int to
    );


    // ======================================
    // RESULTS
    // ======================================

    void displaySimulationResults();


    int getPassengerCount();

    int getCompletedPassengers();

    int getWaitingPassengers();

    int getUnablePassengers();
};

#endif

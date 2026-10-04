#ifndef PROFILER_H
#define PROFILER_H

#include <iostream>
#include <chrono>

#include "Graph.h"
#include "PassengerSimulation.h"

using namespace std;

class Profiler
{
private:
    double simulationTime;
    double bfsTime;

public:

    Profiler();

    void startTimer();

    void stopSimulationTimer();

    void stopBFSTimer();

    double getSimulationTime();

    double getBFSTime();

    void setSimulationTime(double time);

    double measureBFS(
        PassengerSimulation& passengerSimulation,
        Graph& city,
        int start,
        int destination,
        int repetitions
    );

    void displayEfficiencyReport(
        PassengerSimulation& passengerSimulation
    );
};

#endif
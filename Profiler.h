#ifndef PROFILER_H
#define PROFILER_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

#include "Graph.h"
#include "Passenger.h"

struct ProfilingReport
{
    int totalPassengersSimulated = 0;
    int successfulJourneys = 0;
    double averageHops = 0.0;
    double averageTravelTimeMin = 0.0;
    double averageDistanceKm = 0.0;
    int trainOnlyCount = 0;
    int busOnlyCount = 0;
    int multiModalCount = 0;
    long long totalBfsComputationTimeMicroseconds = 0;
    double queriesPerSecond = 0.0;
    double estimatedCo2SavedKg = 0.0;
    std::unordered_map<std::string, int> routePassengerLoad;
};

class Profiler
{
public:
    Profiler();

    static ProfilingReport profileSimulation(const Graph& city, const std::vector<Passenger>& passengers);

    static void displayEfficiencyReport(const ProfilingReport& rep);
};

#endif

#ifndef PASSENGERSIMULATION_H
#define PASSENGERSIMULATION_H

#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Graph.h"
#include "Passenger.h"

class PassengerSimulation
{
private:
    const Graph& city;
    std::mt19937 rng;

public:
    PassengerSimulation(const Graph& g);

    std::vector<Passenger> generatePassengerDemand(TimeOfDay period, int count);

    static void printItineraryDetails(const Graph& city, const Itinerary& itin);

    static TimeDemandInfo analyzeTimeAndDemand(const std::string& timeInput, int origin, int dest, const Itinerary& itin);
    static void printTimeDemandAnalysis(const TimeDemandInfo& info);
    static void printItineraryDetailsWithDemand(const Graph& city, const Itinerary& itin, const TimeDemandInfo& info);

    void runRequirement3Demo() const;
};

#endif

#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

using namespace std;

enum class PassengerStatus
{
    WAITING,
    TRAVELLING,
    COMPLETED,
    UNABLE
};

struct Passenger
{
    int passengerId;

    int origin;
    int destination;

    string demandTime;

    int currentLocation;

    PassengerStatus status;

    int transfers;

    int travelTime;
};

#endif

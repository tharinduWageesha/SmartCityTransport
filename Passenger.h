#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <vector>

enum class Mode
{
    TRAIN,
    BUS,
    WALK_TRANSFER
};

std::string modeToString(Mode m);
std::string modeTag(Mode m);

enum class StationType
{
    BUS_STOP_ONLY,
    TRAIN_STATION_ONLY,
    INTERMODAL_HUB
};

std::string stationTypeToString(StationType st);

enum class TimeOfDay
{
    MORNING_PEAK,
    MIDDAY_OFFPEAK,
    EVENING_PEAK,
    NIGHT_HOURS
};

std::string timeOfDayToString(TimeOfDay t);

struct Passenger
{
    std::string id;
    std::string name;
    int origin;
    int destination;
    std::string departureTime;
    TimeOfDay timePeriod;
    bool requiresMultiModal;
};

struct TripStep
{
    int fromStation;
    int toStation;
    Mode mode;
    std::string routeName;
    int timeMin;
    double distKm;
};

struct Itinerary
{
    bool found = false;
    int origin = -1;
    int destination = -1;
    std::vector<TripStep> steps;
    int totalTimeMin = 0;
    double totalDistKm = 0.0;
    int transfers = 0;
    int busLegs = 0;
    int trainLegs = 0;
};

struct TimeDemandInfo
{
    int hour = 8;
    int minute = 0;
    std::string formattedTime = "08:00 AM";
    TimeOfDay period = TimeOfDay::MORNING_PEAK;
    bool isPeakHour = true;
    std::string periodName = "Morning Peak Hour";
    int networkPaxPerHour = 1800;
    double peakFactor = 2.5;
    int routePaxPerHour = 220;
    int occupancyPercent = 85;
    std::string crowdingLevel = "HIGH (Standing room only)";
    int headwayMin = 6;
    int avgWaitMin = 3;
    int dwellBufferMin = 2;
    int adjustedTotalTimeMin = 0;
};

#endif

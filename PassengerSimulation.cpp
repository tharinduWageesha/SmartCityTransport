#include "PassengerSimulation.h"
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cctype>
#include <algorithm>

PassengerSimulation::PassengerSimulation(const Graph& g)
    : city(g), rng(12345)
{
}

std::vector<Passenger> PassengerSimulation::generatePassengerDemand(TimeOfDay period, int count)
{
    std::vector<Passenger> list;
    list.reserve(count);

    int n = city.getStationCount();
    std::uniform_int_distribution<int> allStations(0, n - 1);

    for (int i = 1; i <= count; ++i)
    {
        std::stringstream ss;
        ss << "PAX-" << std::setfill('0') << std::setw(4) << i;
        std::string id = ss.str();

        int origin = 0;
        int dest = 0;
        std::string depTime = "";
        bool multiModal = false;

        if (period == TimeOfDay::MORNING_PEAK)
        {
            // Commuters traveling from residential (Home) and terminals toward University, Hospital, Mall
            std::discrete_distribution<int> origDist({30, 25, 20, 10, 5, 10});
            std::discrete_distribution<int> destDist({5, 15, 15, 25, 20, 20});

            origin = origDist(rng);
            dest = destDist(rng);
            while (dest == origin) dest = (dest + 1) % n;

            int minute = std::uniform_int_distribution<int>(0, 59)(rng);
            int hour = std::uniform_int_distribution<int>(7, 8)(rng);
            std::stringstream timeStream;
            timeStream << "0" << hour << ":" << std::setw(2) << std::setfill('0') << minute << " AM";
            depTime = timeStream.str();
            multiModal = true;
        }
        else if (period == TimeOfDay::MIDDAY_OFFPEAK)
        {
            origin = allStations(rng);
            dest = allStations(rng);
            while (dest == origin) dest = (dest + 1) % n;

            int minute = std::uniform_int_distribution<int>(0, 59)(rng);
            int hour = std::uniform_int_distribution<int>(11, 14)(rng);
            std::stringstream timeStream;
            timeStream << std::setw(2) << std::setfill('0') << hour << ":"
                       << std::setw(2) << std::setfill('0') << minute << " PM";
            depTime = timeStream.str();
        }
        else if (period == TimeOfDay::EVENING_PEAK)
        {
            // Commuters returning toward Home and Main Stations
            std::discrete_distribution<int> origDist({5, 15, 15, 25, 20, 20});
            std::discrete_distribution<int> destDist({35, 25, 20, 5, 5, 10});

            origin = origDist(rng);
            dest = destDist(rng);
            while (dest == origin) dest = (dest + 1) % n;

            int minute = std::uniform_int_distribution<int>(0, 59)(rng);
            int hour = std::uniform_int_distribution<int>(17, 18)(rng);
            std::stringstream timeStream;
            timeStream << "0" << (hour - 12) << ":" << std::setw(2) << std::setfill('0') << minute << " PM";
            depTime = timeStream.str();
            multiModal = true;
        }
        else
        {
            origin = allStations(rng);
            dest = allStations(rng);
            while (dest == origin) dest = (dest + 1) % n;

            int hour = std::uniform_int_distribution<int>(22, 23)(rng);
            int minute = std::uniform_int_distribution<int>(0, 59)(rng);
            std::stringstream timeStream;
            timeStream << hour << ":" << std::setw(2) << std::setfill('0') << minute << " PM";
            depTime = timeStream.str();
        }

        std::string name = "Passenger " + std::to_string(i);
        list.push_back({id, name, origin, dest, depTime, period, multiModal});
    }

    return list;
}

void PassengerSimulation::printItineraryDetails(const Graph& city, const Itinerary& itin)
{
    if (!itin.found)
    {
        std::cout << "  [!] No route found through the transit network.\n";
        return;
    }

    std::cout << "\n  Route Found: " << city.getStation(itin.origin).name 
              << " -> " << city.getStation(itin.destination).name << "\n";
    std::cout << "  --------------------------------------------------\n";
    std::cout << "  Hops: " << itin.steps.size() 
              << " | Transfers: " << itin.transfers 
              << " | Est. Travel Time: " << itin.totalTimeMin << " mins\n";
    std::cout << "  Transit Mode Breakdown: " 
              << itin.trainLegs << " Train leg(s), " 
              << itin.busLegs << " Bus leg(s)\n";
    std::cout << "  --------------------------------------------------\n";
    std::cout << "  Step-by-Step Directions:\n";

    for (size_t i = 0; i < itin.steps.size(); ++i)
    {
        const auto& step = itin.steps[i];
        std::cout << "   " << (i + 1) << ". " << modeTag(step.mode) << " " 
                  << step.routeName << "\n";
        std::cout << "      From : " << city.getStation(step.fromStation).name << "\n";
        std::cout << "      To   : " << city.getStation(step.toStation).name 
                  << " (" << step.timeMin << " mins)\n";

        if (i + 1 < itin.steps.size())
        {
            const auto& nextStep = itin.steps[i + 1];
            if (nextStep.mode != step.mode || nextStep.routeName != step.routeName)
            {
                std::cout << "      >>> TRANSFER: Switch from " << modeToString(step.mode) 
                          << " to " << modeToString(nextStep.mode) 
                          << " at " << city.getStation(step.toStation).name << "\n";
            }
        }
    }
    std::cout << "\n";
}

void PassengerSimulation::runRequirement3Demo() const
{
    std::cout << "\n==================================================\n";
    std::cout << "  VARIABLE PASSENGER DEMAND SIMULATION\n";
    std::cout << "==================================================\n";
    std::cout << "Requirement III specifies:\n";
    std::cout << "\"At 7.00 AM, passenger X will travel from location A to\n";
    std::cout << " Location C via Location B by first using train and then bus.\"\n";
    std::cout << "--------------------------------------------------\n";

    std::cout << "\n>>> DEMONSTRATION SCENARIO (Requirement III): <<<\n";
    std::cout << "Passenger      : Passenger X (Kasun Perera)\n";
    std::cout << "Departure Time : 07:00 AM (Morning Peak)\n";
    std::cout << "Location A     : Railway Station (Origin)\n";
    std::cout << "Location B     : Bus Terminal (Intermodal Transfer Hub)\n";
    std::cout << "Location C     : Hospital (Destination)\n";
    std::cout << "Plan           : Step 1 (Train A -> B) | Step 2 (Bus B -> C)\n";

    int locA = 2; // Railway Station
    int locB = 1; // Bus Terminal
    int locC = 4; // Hospital

    Itinerary multiModalItin = city.findMultiModalJourneyBFS(locA, locB, locC, Mode::TRAIN, Mode::BUS);
    printItineraryDetails(city, multiModalItin);

    std::cout << "--------------------------------------------------\n";
    std::cout << "  VARIABLE PASSENGER DEMANDS BY TIME OF DAY\n";
    std::cout << "--------------------------------------------------\n";

    PassengerSimulation tempSim(city);
    std::vector<TimeOfDay> periods = {
        TimeOfDay::MORNING_PEAK,
        TimeOfDay::MIDDAY_OFFPEAK,
        TimeOfDay::EVENING_PEAK,
        TimeOfDay::NIGHT_HOURS
    };

    for (auto p : periods)
    {
        std::cout << "\n  [" << timeOfDayToString(p) << "]\n";
        auto samplePax = tempSim.generatePassengerDemand(p, 2);
        for (const auto& pax : samplePax)
        {
            Itinerary it = city.findPathBFS(pax.origin, pax.destination);
            std::cout << "   * " << pax.departureTime << " | " << pax.name << "\n";
            std::cout << "     " << city.getStation(pax.origin).name 
                      << " -> " << city.getStation(pax.destination).name 
                      << " (" << it.steps.size() << " hops, " << it.totalTimeMin << " min) ";
            if (it.trainLegs > 0 && it.busLegs > 0) std::cout << "[Multi-modal: Train + Bus]\n";
            else if (it.trainLegs > 0) std::cout << "[Train Direct]\n";
            else std::cout << "[Bus Direct]\n";
        }
    }
    std::cout << "\n";
}

TimeDemandInfo PassengerSimulation::analyzeTimeAndDemand(const std::string& timeInput, int origin, int dest, const Itinerary& itin)
{
    TimeDemandInfo info;
    int hour = 8;
    int minute = 0;

    std::string s = timeInput;
    std::string lower = "";
    for (char c : s) lower += (char)std::tolower(c);
    bool hasPM = (lower.find("pm") != std::string::npos || lower.find("p.m.") != std::string::npos);
    bool hasAM = (lower.find("am") != std::string::npos || lower.find("a.m.") != std::string::npos);

    int colonPos = (int)s.find(':');
    if (colonPos != (int)std::string::npos)
    {
        std::string hStr = "";
        for (int i = 0; i < colonPos; ++i)
        {
            if (std::isdigit(s[i])) hStr += s[i];
        }
        if (!hStr.empty()) hour = std::stoi(hStr);

        std::string mStr = "";
        for (size_t i = colonPos + 1; i < s.size(); ++i)
        {
            if (std::isdigit(s[i])) mStr += s[i];
            else if (!mStr.empty() && !std::isdigit(s[i])) break;
        }
        if (!mStr.empty()) minute = std::stoi(mStr);
    }
    else
    {
        std::string numStr = "";
        for (char c : s)
        {
            if (std::isdigit(c)) numStr += c;
            else if (!numStr.empty()) break;
        }
        if (!numStr.empty())
        {
            int val = std::stoi(numStr);
            if (val >= 0 && val <= 23) hour = val;
        }
    }

    if (hasPM && hour < 12) hour += 12;
    if (hasAM && hour == 12) hour = 0;

    if (hour < 0) hour = 0;
    if (hour > 23) hour = 23;
    if (minute < 0) minute = 0;
    if (minute > 59) minute = 59;

    info.hour = hour;
    info.minute = minute;

    int displayHour = hour % 12;
    if (displayHour == 0) displayHour = 12;
    std::string ampm = (hour >= 12) ? "PM" : "AM";
    std::stringstream timeSS;
    timeSS << std::setw(2) << std::setfill('0') << displayHour << ":"
           << std::setw(2) << std::setfill('0') << minute << " " << ampm;
    info.formattedTime = timeSS.str();

    double t = hour + (minute / 60.0);

    if (t >= 6.5 && t <= 9.5) // 06:30 - 09:30
    {
        info.period = TimeOfDay::MORNING_PEAK;
        info.isPeakHour = true;
        info.periodName = "Morning Peak Hours (06:30 - 09:30 AM)";
        
        double diff = std::abs(t - 7.75) / 1.5;
        if (diff > 1.0) diff = 1.0;
        info.networkPaxPerHour = 1450 + (int)(500 * (1.0 - diff * diff));
        info.peakFactor = 2.6;
        info.occupancyPercent = 82 + (int)(14 * (1.0 - diff));
        info.crowdingLevel = "HIGH (Standing room only / Heavy boarding)";
        info.headwayMin = 5;
        info.avgWaitMin = 3;
        info.dwellBufferMin = 2;
    }
    else if (t >= 16.5 && t <= 19.5) // 16:30 - 19:30
    {
        info.period = TimeOfDay::EVENING_PEAK;
        info.isPeakHour = true;
        info.periodName = "Evening Peak Hours (04:30 - 07:30 PM)";

        double diff = std::abs(t - 17.75) / 1.5;
        if (diff > 1.0) diff = 1.0;
        info.networkPaxPerHour = 1500 + (int)(550 * (1.0 - diff * diff));
        info.peakFactor = 2.8;
        info.occupancyPercent = 85 + (int)(12 * (1.0 - diff));
        info.crowdingLevel = "HIGH (Heavy evening commuter demand)";
        info.headwayMin = 5;
        info.avgWaitMin = 3;
        info.dwellBufferMin = 2;
    }
    else if (t > 9.5 && t < 16.5) // 09:31 - 16:29
    {
        info.period = TimeOfDay::MIDDAY_OFFPEAK;
        info.isPeakHour = false;
        info.periodName = "Midday Regular Hours (09:31 AM - 04:29 PM)";

        info.networkPaxPerHour = 520 + (int)(80 * std::sin((t - 9.5) * 3.14159 / 7.0));
        info.peakFactor = 1.0;
        info.occupancyPercent = 38 + (int)(7 * std::sin((t - 9.5) * 3.14159 / 7.0));
        info.crowdingLevel = "MODERATE (Comfortable seating readily available)";
        info.headwayMin = 10;
        info.avgWaitMin = 5;
        info.dwellBufferMin = 0;
    }
    else // Night hours
    {
        info.period = TimeOfDay::NIGHT_HOURS;
        info.isPeakHour = false;
        info.periodName = "Night Off-Peak Hours (07:31 PM - 06:29 AM)";

        info.networkPaxPerHour = 90 + (int)(70 * (t > 19.5 ? (24.0 - t) / 4.5 : t / 6.5));
        if (info.networkPaxPerHour < 70) info.networkPaxPerHour = 70;
        info.peakFactor = 0.25;
        info.occupancyPercent = 15;
        info.crowdingLevel = "LOW (Uncrowded / High seat availability)";
        info.headwayMin = 15;
        info.avgWaitMin = 8;
        info.dwellBufferMin = 0;
    }

    double routeFactor = 0.12;
    if (info.isPeakHour)
    {
        if ((origin == 0 || origin == 2) && (dest == 3 || dest == 4)) routeFactor = 0.18;
        else if ((origin == 3 || origin == 4) && (dest == 0 || dest == 1)) routeFactor = 0.18;
    }
    info.routePaxPerHour = std::max(15, (int)(info.networkPaxPerHour * routeFactor));
    info.adjustedTotalTimeMin = itin.totalTimeMin + (info.isPeakHour ? (info.dwellBufferMin * std::max(1, (int)itin.steps.size())) : 0);

    return info;
}

void PassengerSimulation::printTimeDemandAnalysis(const TimeDemandInfo& info)
{
    std::cout << "\n==================================================\n";
    std::cout << "     TIME & PASSENGER DEMAND ANALYSIS REPORT      \n";
    std::cout << "==================================================\n";
    std::cout << "  Input Departure Time : " << info.formattedTime << "\n";
    std::cout << "  Transit Time Period  : " << info.periodName << "\n";
    std::cout << "  Operational Regime   : " 
              << (info.isPeakHour ? ">>> PEAK HOURS (High Demand Surge) <<<" : ">>> REGULAR HOURS (Standard Baseline Flow) <<<") << "\n";
    std::cout << "  Estimated City Demand: ~" << info.networkPaxPerHour << " passengers/hour (Load Factor: " << info.peakFactor << "x)\n";
    std::cout << "  Corridor Route Demand: ~" << info.routePaxPerHour << " passengers/hour along this line\n";
    std::cout << "==================================================\n";
}

void PassengerSimulation::printItineraryDetailsWithDemand(const Graph& city, const Itinerary& itin, const TimeDemandInfo& info)
{
    printTimeDemandAnalysis(info);

    if (!itin.found)
    {
        std::cout << "  [!] No route found through the transit network.\n";
        return;
    }

    std::cout << "\n  Route Found: " << city.getStation(itin.origin).name 
              << " -> " << city.getStation(itin.destination).name << "\n";
    std::cout << "  --------------------------------------------------\n";
    std::cout << "  Hops: " << itin.steps.size() 
              << " | Transfers: " << itin.transfers 
              << " | Est. Travel Time: " << itin.totalTimeMin << " mins\n";
    std::cout << "  Transit Mode Breakdown: " 
              << itin.trainLegs << " Train leg(s), " 
              << itin.busLegs << " Bus leg(s)\n";
    std::cout << "  --------------------------------------------------\n";
    std::cout << "  Step-by-Step Directions:\n";

    for (size_t i = 0; i < itin.steps.size(); ++i)
    {
        const auto& step = itin.steps[i];
        std::cout << "   " << (i + 1) << ". " << modeTag(step.mode) << " " 
                  << step.routeName << "\n";
        std::cout << "      From : " << city.getStation(step.fromStation).name << "\n";
        std::cout << "      To   : " << city.getStation(step.toStation).name 
                  << " (" << step.timeMin << " mins)\n";

        if (i + 1 < itin.steps.size())
        {
            const auto& nextStep = itin.steps[i + 1];
            if (nextStep.mode != step.mode || nextStep.routeName != step.routeName)
            {
                std::cout << "      >>> TRANSFER: Switch from " << modeToString(step.mode) 
                          << " to " << modeToString(nextStep.mode) 
                          << " at " << city.getStation(step.toStation).name << "\n";
            }
        }
    }
    std::cout << "\n";
}

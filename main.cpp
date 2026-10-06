#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Graph.h"
#include "BusNetwork.h"
#include "TrainNetwork.h"
#include "PassengerSimulation.h"
#include "Profiler.h"

void buildImaginativeCity(Graph& city, BusNetwork& busNetwork, TrainNetwork& trainNetwork)
{
    int s0 = city.addStation("Home", "Residential Zone", StationType::BUS_STOP_ONLY);
    int s1 = city.addStation("Bus Terminal", "Central Transit Hub", StationType::INTERMODAL_HUB);
    int s2 = city.addStation("Railway Station", "Main Metro Hub", StationType::INTERMODAL_HUB);
    int s3 = city.addStation("University", "Education Zone", StationType::INTERMODAL_HUB);
    int s4 = city.addStation("Hospital", "Healthcare Zone", StationType::INTERMODAL_HUB);
    int s5 = city.addStation("Shopping Mall", "Commercial Zone", StationType::BUS_STOP_ONLY);

    // Bus Routes (Part I)
    busNetwork.registerBusRoute(city, {
        "BUS-101",
        "Route 101 (Home - Terminal - University)",
        Mode::BUS,
        {s0, s1, s3},
        10,
        50
    });

    busNetwork.registerBusRoute(city, {
        "BUS-102",
        "Route 102 (Terminal - Hospital - Shopping Mall)",
        Mode::BUS,
        {s1, s4, s5},
        8,
        40
    });

    busNetwork.registerBusRoute(city, {
        "BUS-103",
        "Route 103 (Home - Terminal - Hospital)",
        Mode::BUS,
        {s0, s1, s4},
        12,
        45
    });

    busNetwork.registerBusRoute(city, {
        "BUS-104",
        "Route 104 (University - Shopping Mall)",
        Mode::BUS,
        {s3, s5},
        15,
        50
    });

    // Train Routes (Part II)
    trainNetwork.registerTrainRoute(city, {
        "TRAIN-201",
        "Metro 201 (Railway Station - University)",
        Mode::TRAIN,
        {s2, s3},
        6,
        300
    });

    trainNetwork.registerTrainRoute(city, {
        "TRAIN-202",
        "Metro 202 (Railway Station - Shopping Mall)",
        Mode::TRAIN,
        {s2, s5},
        8,
        250
    });

    trainNetwork.registerTrainRoute(city, {
        "TRAIN-203",
        "Shuttle 203 (Railway Station - Bus Terminal)",
        Mode::TRAIN,
        {s2, s1},
        5,
        350
    });
}

void printBanner()
{
    std::cout << "\n==================================================\n";
    std::cout << "   SMART CITY PUBLIC TRANSPORTATION SIMULATION    \n";
    std::cout << "   Graph Theory & Multi-Modal Transit Model (C++) \n";
    std::cout << "==================================================\n";
}

void interactiveJourneyPlanner(const Graph& city)
{
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "  INTERACTIVE JOURNEY PLANNER (BFS)\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "Available Locations in City:\n";
    for (const auto& s : city.getAllStations())
    {
        std::cout << "  [" << s.id << "] " << std::left << std::setw(18) << s.name 
                  << " (" << s.zone << ")\n";
    }

    std::cout << "\nEnter Origin ID (0 to " << (city.getStationCount() - 1) << "): ";
    int origId;
    if (!(std::cin >> origId) || origId < 0 || origId >= city.getStationCount())
    {
        std::cout << "Invalid Origin ID. Returning to menu.\n";
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        return;
    }

    std::cout << "Enter Destination ID (0 to " << (city.getStationCount() - 1) << "): ";
    int destId;
    if (!(std::cin >> destId) || destId < 0 || destId >= city.getStationCount())
    {
        std::cout << "Invalid Destination ID. Returning to menu.\n";
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        return;
    }

    std::cout << "\nEnter Departure Time (e.g., 07:30, 14:00, or 24h HH:MM) [default 08:00 AM]: ";
    std::string timeInput;
    char nextChar = std::cin.peek();
    if (nextChar == '\n' || nextChar == '\r')
    {
        std::cin.get();
        if (std::cin.peek() == '\n') std::cin.get();
    }
    std::getline(std::cin, timeInput);
    size_t firstNonSpace = timeInput.find_first_not_of(" \t\r\n");
    if (firstNonSpace == std::string::npos)
    {
        timeInput = "08:00 AM";
    }
    else
    {
        size_t lastNonSpace = timeInput.find_last_not_of(" \t\r\n");
        timeInput = timeInput.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
    }

    std::cout << "\nRouting Mode:\n";
    std::cout << "  1. Multi-modal (Train + Bus auto)\n";
    std::cout << "  2. Bus Only\n";
    std::cout << "  3. Train Only\n";
    std::cout << "Select (1-3): ";
    int pref;
    if (!(std::cin >> pref))
    {
        pref = 1;
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    Mode modeFilter = Mode::WALK_TRANSFER;
    if (pref == 2) modeFilter = Mode::BUS;
    else if (pref == 3) modeFilter = Mode::TRAIN;

    Itinerary itin = city.findPathBFS(origId, destId, modeFilter);
    TimeDemandInfo demand = PassengerSimulation::analyzeTimeAndDemand(timeInput, origId, destId, itin);
    PassengerSimulation::printItineraryDetailsWithDemand(city, itin, demand);
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    Graph city;
    BusNetwork busNetwork;
    TrainNetwork trainNetwork;
    buildImaginativeCity(city, busNetwork, trainNetwork);

    PassengerSimulation passengerSim(city);

    printBanner();
    std::cout << "City Graph Initialized: " << city.getStationCount() 
              << " Locations | " << city.getEdgeCount() << " Transit Corridors\n";
    std::cout << "Transit Policy: 100% Public Transportation Allowed\n";

    while (true)
    {
        std::cout << "\n==================================================\n";
        std::cout << "                MAIN SIMULATION MENU              \n";
        std::cout << "==================================================\n";
        std::cout << "1. Display City Network & Locations\n";
        std::cout << "2. Simulate Bus Routes & Network\n";
        std::cout << "3. Simulate Train Routes & Network\n";
        std::cout << "4. Variable Passenger Demand & Req III Demo\n";
        std::cout << "5. System Profiling & Efficiency Report\n";
        std::cout << "6. Interactive Journey Planner (BFS Route Finder)\n";
        std::cout << "7. Run Complete Automated Simulation\n";
        std::cout << "8. Exit\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "Enter your choice (1-8): ";

        int choice;
        if (!(std::cin >> choice))
        {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::string dummy;
            std::getline(std::cin, dummy);
            std::cout << "Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                city.displayLocations();
                break;
            case 2:
                busNetwork.displayBusNetwork(city);
                break;
            case 3:
                trainNetwork.displayTrainNetwork(city);
                break;
            case 4:
                passengerSim.runRequirement3Demo();
                break;
            case 5:
            {
                std::cout << "\nBenchmarking 100 passenger trips under peak demand...\n";
                auto morningPax = passengerSim.generatePassengerDemand(TimeOfDay::MORNING_PEAK, 100);
                ProfilingReport rep = Profiler::profileSimulation(city, morningPax);
                Profiler::displayEfficiencyReport(rep);
                break;
            }
            case 6:
                interactiveJourneyPlanner(city);
                break;
            case 7:
            {
                std::cout << "\n>>> RUNNING COMPLETE DEMONSTRATION OF ALL REQUIREMENTS <<<\n";
                city.displayLocations();
                busNetwork.displayBusNetwork(city);
                trainNetwork.displayTrainNetwork(city);
                passengerSim.runRequirement3Demo();
                
                std::cout << "\nBenchmarking 100 passenger trips under peak demand...\n";
                auto morningPax = passengerSim.generatePassengerDemand(TimeOfDay::MORNING_PEAK, 100);
                ProfilingReport rep = Profiler::profileSimulation(city, morningPax);
                Profiler::displayEfficiencyReport(rep);
                break;
            }
            case 8:
                std::cout << "\nExiting Smart City Transport Simulation. Thank you!\n\n";
                return 0;
            default:
                std::cout << "Choice out of range. Please choose 1-8.\n";
                break;
        }
    }

    return 0;
}

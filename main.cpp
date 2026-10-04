#include <iostream>
#include <chrono>
#include <limits>

#include "Graph.h"
#include "BusNetwork.h"
#include "TrainNetwork.h"
#include "PassengerSimulation.h"
#include "Profiler.h"

using namespace std;

// ==========================================
// DISPLAY MAIN MENU
// ==========================================

void displayMenu()
{
    cout << "\n";
    cout << "==========================================\n";
    cout << "   SMART CITY PUBLIC TRANSPORT SYSTEM\n";
    cout << "==========================================\n";

    cout << "\n1. Display City Network";
    cout << "\n2. Bus Network Tests";
    cout << "\n3. Train Network Tests";
    cout << "\n4. BFS Route Finding";
    cout << "\n5. Passenger Demand & Simulation";
    cout << "\n6. Efficiency & Profiling Report";
    cout << "\n7. Run Complete System Test";
    cout << "\n8. Exit";

    cout << "\n\nEnter your choice: ";
}

// ==========================================
// DISPLAY CITY NETWORK
// ==========================================

void displayCityNetwork(
    Graph& city,
    BusNetwork& busNetwork,
    TrainNetwork& trainNetwork
)
{
    cout << "\n======================================\n";
    cout << "          CITY TRANSPORT NETWORK\n";
    cout << "======================================\n";

    city.displayLocations();

    city.displayConnections();

    busNetwork.displayBusRoutes(city);

    trainNetwork.displayTrainRoutes(city);
}

// ==========================================
// BUS NETWORK TESTS
// ==========================================

void runBusTests(
    Graph& city,
    BusNetwork& busNetwork,
    int terminal,
    int home,
    int university
)
{
    cout << "\n======================================\n";
    cout << "            BUS NETWORK TESTS\n";
    cout << "======================================\n";

    // --------------------------------------
    // BUS SEARCH
    // --------------------------------------

    cout << "\n===== BUS SEARCH =====\n";

    busNetwork.displayBusesAtStop(
        terminal
    );

    // --------------------------------------
    // BUS ROUTE TEST
    // --------------------------------------

    cout << "\n===== BUS ROUTE TEST =====\n";

    cout << "Can travel from "
         << city.getLocationName(home)
         << " to "
         << city.getLocationName(university)
         << " by bus: ";

    if (busNetwork.canTravelByBus(
            home,
            university))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    // --------------------------------------
    // BUS SCHEDULE TEST
    // --------------------------------------

    cout << "\n===== BUS SCHEDULE TEST =====\n";

    if (busNetwork.isBusOperating(
            0,
            "10:00"))
    {
        cout << "Bus 101 is operating at 10:00."
             << endl;
    }
    else
    {
        cout << "Bus 101 is not operating at 10:00."
             << endl;
    }

    if (busNetwork.isBusOperating(
            0,
            "23:00"))
    {
        cout << "Bus 101 is operating at 23:00."
             << endl;
    }
    else
    {
        cout << "Bus 101 is not operating at 23:00."
             << endl;
    }

    // --------------------------------------
    // PASSENGER CAPACITY TEST
    // --------------------------------------

    cout << "\n===== BUS PASSENGER TEST =====\n";

    if (busNetwork.boardPassengers(
            0,
            20))
    {
        cout << "20 passengers boarded Bus 101."
             << endl;
    }
    else
    {
        cout << "Passengers could not board Bus 101."
             << endl;
    }

    cout << "Available seats on Bus 101: "
         << busNetwork.getAvailableCapacity(0)
         << endl;

    if (busNetwork.leavePassengers(
            0,
            5))
    {
        cout << "5 passengers left Bus 101."
             << endl;
    }

    busNetwork.displayBusStatus();
}

// ==========================================
// TRAIN NETWORK TESTS
// ==========================================

void runTrainTests(
    Graph& city,
    TrainNetwork& trainNetwork,
    int station,
    int university
)
{
    cout << "\n======================================\n";
    cout << "           TRAIN NETWORK TESTS\n";
    cout << "======================================\n";

    // --------------------------------------
    // TRAIN SEARCH
    // --------------------------------------

    cout << "\n===== TRAIN SEARCH =====\n";

    trainNetwork.displayTrainsAtStation(
        station
    );

    // --------------------------------------
    // TRAIN ROUTE TEST
    // --------------------------------------

    cout << "\n===== TRAIN ROUTE TEST =====\n";

    cout << "Can travel from "
         << city.getLocationName(station)
         << " to "
         << city.getLocationName(university)
         << " by train: ";

    if (trainNetwork.canTravelByTrain(
            station,
            university))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    // --------------------------------------
    // TRAIN SCHEDULE TEST
    // --------------------------------------

    cout << "\n===== TRAIN SCHEDULE TEST =====\n";

    if (trainNetwork.isTrainOperating(
            0,
            "10:00"))
    {
        cout << "Train 201 is operating at 10:00."
             << endl;
    }
    else
    {
        cout << "Train 201 is not operating at 10:00."
             << endl;
    }

    if (trainNetwork.isTrainOperating(
            0,
            "23:30"))
    {
        cout << "Train 201 is operating at 23:30."
             << endl;
    }
    else
    {
        cout << "Train 201 is not operating at 23:30."
             << endl;
    }

    // --------------------------------------
    // TRAIN CAPACITY TEST
    // --------------------------------------

    cout << "\n===== TRAIN PASSENGER TEST =====\n";

    if (trainNetwork.boardPassengers(
            0,
            120))
    {
        cout << "120 passengers boarded Train 201."
             << endl;
    }
    else
    {
        cout << "Passengers could not board Train 201."
             << endl;
    }

    cout << "Available seats on Train 201: "
         << trainNetwork.getAvailableCapacity(0)
         << endl;

    if (trainNetwork.leavePassengers(
            0,
            30))
    {
        cout << "30 passengers left Train 201."
             << endl;
    }

    trainNetwork.displayTrainStatus();
}

// ==========================================
// BFS TEST
// ==========================================

void runBFSTest(
    Graph& city,
    TrainNetwork& trainNetwork,
    int home,
    int mall
)
{
    cout << "\n======================================\n";
    cout << "             BFS ROUTE TEST\n";
    cout << "======================================\n";

    trainNetwork.findRouteBFS(
        city,
        home,
        mall
    );
}

// ==========================================
// PASSENGER DEMAND & SIMULATION
// ==========================================

void runPassengerSimulation(
    Graph& city,
    BusNetwork& busNetwork,
    TrainNetwork& trainNetwork,
    PassengerSimulation& passengerSimulation,
    Profiler& profiler
)
{
    cout << "\n======================================\n";
    cout << "       MEMBER 3 - PASSENGER SIMULATION\n";
    cout << "======================================\n";

    // --------------------------------------
    // MORNING DEMAND
    // --------------------------------------

    cout << "\n===== MORNING DEMAND =====\n";

    passengerSimulation.generateDemand(
        city,
        "Morning",
        10
    );

    // --------------------------------------
    // AFTERNOON DEMAND
    // --------------------------------------

    cout << "\n===== AFTERNOON DEMAND =====\n";

    passengerSimulation.generateDemand(
        city,
        "Afternoon",
        5
    );

    // --------------------------------------
    // EVENING DEMAND
    // --------------------------------------

    cout << "\n===== EVENING DEMAND =====\n";

    passengerSimulation.generateDemand(
        city,
        "Evening",
        8
    );

    // --------------------------------------
    // DEMAND STATISTICS
    // --------------------------------------

    passengerSimulation.displayDemandStatistics();

    // --------------------------------------
    // PASSENGER LIST
    // --------------------------------------

    passengerSimulation.displayPassengers(
        city
    );

    // --------------------------------------
    // SIMULATION
    // --------------------------------------

    cout << "\n===== JOURNEY SIMULATION =====\n";

    auto startTime =
        chrono::high_resolution_clock::now();

    passengerSimulation.simulateJourneys(
        city,
        busNetwork,
        trainNetwork,
        "10:00"
    );

    auto endTime =
        chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed =
        endTime - startTime;

    profiler.setSimulationTime(
        elapsed.count()
    );

    // --------------------------------------
    // RESULTS
    // --------------------------------------

    passengerSimulation.displaySimulationResults();

    // --------------------------------------
    // FINAL STATUS
    // --------------------------------------

    cout << "\n===== FINAL PASSENGER STATUS =====\n";

    passengerSimulation.displayPassengers(
        city
    );

    cout << "\nPassenger simulation completed."
         << endl;
}

// ==========================================
// RUN COMPLETE SYSTEM TEST
// ==========================================

void runCompleteSystemTest(
    Graph& city,
    BusNetwork& busNetwork,
    TrainNetwork& trainNetwork,
    PassengerSimulation& passengerSimulation,
    Profiler& profiler,
    int home,
    int terminal,
    int station,
    int university,
    int mall
)
{
    cout << "\n";
    cout << "==========================================\n";
    cout << "          COMPLETE SYSTEM TEST\n";
    cout << "==========================================\n";

    displayCityNetwork(
        city,
        busNetwork,
        trainNetwork
    );

    runBusTests(
        city,
        busNetwork,
        terminal,
        home,
        university
    );

    runTrainTests(
        city,
        trainNetwork,
        station,
        university
    );

    runBFSTest(
        city,
        trainNetwork,
        home,
        mall
    );

    runPassengerSimulation(
        city,
        busNetwork,
        trainNetwork,
        passengerSimulation,
        profiler
    );

    // --------------------------------------
    // BFS PERFORMANCE TEST
    // --------------------------------------

    cout << "\n===== BFS PERFORMANCE TEST =====\n";

    double bfsTime =
        profiler.measureBFS(
            passengerSimulation,
            city,
            home,
            mall,
            1000
        );

    cout << "Average BFS execution time: "
         << bfsTime
         << " ms"
         << endl;

    // --------------------------------------
    // FINAL EFFICIENCY REPORT
    // --------------------------------------

    profiler.displayEfficiencyReport(
        passengerSimulation
    );

    cout << "\n==========================================\n";
    cout << "       SYSTEM TEST COMPLETED\n";
    cout << "==========================================\n";
}

// ==========================================
// MAIN
// ==========================================

int main()
{
    Graph city;

    BusNetwork busNetwork;

    TrainNetwork trainNetwork;

    PassengerSimulation passengerSimulation;

    Profiler profiler;

    // ======================================
    // CREATE CITY LOCATIONS
    // ======================================

    int home =
        city.addLocation("Home");

    int terminal =
        city.addLocation("Bus Terminal");

    int station =
        city.addLocation("Railway Station");

    int university =
        city.addLocation("University");

    int hospital =
        city.addLocation("Hospital");

    int mall =
        city.addLocation("Shopping Mall");

    // ======================================
    // CREATE BUS CONNECTIONS
    // ======================================

    city.addBidirectionalConnection(
        home,
        terminal,
        8,
        "Bus"
    );

    city.addBidirectionalConnection(
        terminal,
        university,
        12,
        "Bus"
    );

    city.addBidirectionalConnection(
        terminal,
        hospital,
        10,
        "Bus"
    );

    city.addBidirectionalConnection(
        university,
        mall,
        7,
        "Bus"
    );

    city.addBidirectionalConnection(
        hospital,
        mall,
        9,
        "Bus"
    );

    // ======================================
    // CREATE BUS ROUTES
    // ======================================

    busNetwork.addBusRoute(
        101,
        "Home - University",
        {home, terminal, university},
        50,
        "06:00",
        "22:00"
    );

    busNetwork.addBusRoute(
        102,
        "Bus Terminal - Hospital - Mall",
        {terminal, hospital, mall},
        40,
        "06:30",
        "21:30"
    );

    busNetwork.addBusRoute(
        103,
        "Home - Bus Terminal - Hospital",
        {home, terminal, hospital},
        45,
        "07:00",
        "20:00"
    );

    // ======================================
    // CREATE TRAIN ROUTES
    // ======================================

    trainNetwork.addTrainRoute(
        city,
        201,
        "Railway Station - University",
        {station, university},
        10,
        300,
        "05:30",
        "23:00"
    );

    trainNetwork.addTrainRoute(
        city,
        202,
        "Railway Station - Shopping Mall",
        {station, mall},
        8,
        250,
        "06:00",
        "22:00"
    );

    trainNetwork.addTrainRoute(
        city,
        203,
        "Home - Railway Station - University",
        {home, station, university},
        12,
        350,
        "05:00",
        "21:30"
    );

    // ======================================
    // MAIN MENU
    // ======================================

    int choice;

    do
    {
        displayMenu();

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "\nInvalid input."
                 << endl;

            continue;
        }

        switch (choice)
        {
            // ------------------------------
            // DISPLAY NETWORK
            // ------------------------------

            case 1:

                displayCityNetwork(
                    city,
                    busNetwork,
                    trainNetwork
                );

                break;

            // ------------------------------
            // BUS TESTS
            // ------------------------------

            case 2:

                runBusTests(
                    city,
                    busNetwork,
                    terminal,
                    home,
                    university
                );

                break;

            // ------------------------------
            // TRAIN TESTS
            // ------------------------------

            case 3:

                runTrainTests(
                    city,
                    trainNetwork,
                    station,
                    university
                );

                break;

            // ------------------------------
            // BFS
            // ------------------------------

            case 4:

                runBFSTest(
                    city,
                    trainNetwork,
                    home,
                    mall
                );

                break;

            // ------------------------------
            // PASSENGER SIMULATION
            // ------------------------------

            case 5:

                runPassengerSimulation(
                    city,
                    busNetwork,
                    trainNetwork,
                    passengerSimulation,
                    profiler
                );

                break;

            // ------------------------------
            // PROFILING
            // ------------------------------

            case 6:
            {
                cout << "\n===== BFS PERFORMANCE TEST =====\n";

                double bfsTime =
                    profiler.measureBFS(
                        passengerSimulation,
                        city,
                        home,
                        mall,
                        1000
                    );

                cout << "Average BFS execution time: "
                     << bfsTime
                     << " ms"
                     << endl;

                profiler.displayEfficiencyReport(
                    passengerSimulation
                );

                break;
            }

            // ------------------------------
            // COMPLETE TEST
            // ------------------------------

            case 7:

                runCompleteSystemTest(
                    city,
                    busNetwork,
                    trainNetwork,
                    passengerSimulation,
                    profiler,
                    home,
                    terminal,
                    station,
                    university,
                    mall
                );

                break;

            // ------------------------------
            // EXIT
            // ------------------------------

            case 8:

                cout << "\nExiting Smart City "
                     << "Public Transport System..."
                     << endl;

                break;

            // ------------------------------
            // INVALID
            // ------------------------------

            default:

                cout << "\nInvalid choice. "
                     << "Please select 1-8."
                     << endl;
        }

    }
    while (choice != 8);

    return 0;
}
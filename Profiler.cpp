#include "Profiler.h"

Profiler::Profiler()
{
    simulationTime = 0.0;
    bfsTime = 0.0;
}

// ==========================================
// START TIMER
// ==========================================

void Profiler::startTimer()
{
    // Timer initialization is handled
    // inside the measurement functions.
}

// ==========================================
// STOP SIMULATION TIMER
// ==========================================

void Profiler::stopSimulationTimer()
{
    // Reserved for future extension.
}

// ==========================================
// STOP BFS TIMER
// ==========================================

void Profiler::stopBFSTimer()
{
    // Reserved for future extension.
}

// ==========================================
// GET SIMULATION TIME
// ==========================================

double Profiler::getSimulationTime()
{
    return simulationTime;
}

// ==========================================
// GET BFS TIME
// ==========================================

double Profiler::getBFSTime()
{
    return bfsTime;
}

void Profiler::setSimulationTime(double time)
{
    simulationTime = time;
}

// ==========================================
// MEASURE BFS PERFORMANCE
// ==========================================

double Profiler::measureBFS(
    PassengerSimulation& passengerSimulation,
    Graph& city,
    int start,
    int destination,
    int repetitions
)
{
    if (repetitions <= 0)
    {
        repetitions = 1;
    }

    auto startTime =
        chrono::high_resolution_clock::now();

    for (int i = 0;
         i < repetitions;
         i++)
    {
        passengerSimulation.findRouteBFS(
            city,
            start,
            destination
        );
    }

    auto endTime =
        chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed =
        endTime - startTime;

    bfsTime =
        elapsed.count() / repetitions;

    return bfsTime;
}

// ==========================================
// DISPLAY EFFICIENCY REPORT
// ==========================================

void Profiler::displayEfficiencyReport(
    PassengerSimulation& passengerSimulation
)
{
    int total =
        passengerSimulation.getPassengerCount();

    int completed =
        passengerSimulation.getCompletedPassengers();

    int waiting =
        passengerSimulation.getWaitingPassengers();

    int unable =
        passengerSimulation.getUnablePassengers();

    cout << "\n======================================\n";
    cout << "       SYSTEM EFFICIENCY REPORT\n";
    cout << "======================================\n";

    cout << "\n----- PASSENGER PERFORMANCE -----\n";

    cout << "Total Passengers: "
         << total
         << endl;

    cout << "Completed Journeys: "
         << completed
         << endl;

    cout << "Waiting Passengers: "
         << waiting
         << endl;

    cout << "Unable Journeys: "
         << unable
         << endl;

    if (total > 0)
    {
        double completionRate =
            completed * 100.0 / total;

        double unableRate =
            unable * 100.0 / total;

        double waitingRate =
            waiting * 100.0 / total;

        cout << "Completion Rate: "
             << completionRate
             << "%"
             << endl;

        cout << "Unable Rate: "
             << unableRate
             << "%"
             << endl;

        cout << "Waiting Rate: "
             << waitingRate
             << "%"
             << endl;
    }
    else
    {
        cout << "Completion Rate: 0%"
             << endl;

        cout << "Unable Rate: 0%"
             << endl;

        cout << "Waiting Rate: 0%"
             << endl;
    }

    cout << "\n----- ALGORITHM PERFORMANCE -----\n";

    cout << "Average BFS Execution Time: "
         << bfsTime
         << " ms"
         << endl;

    cout << "\n----- SIMULATION PERFORMANCE -----\n";

    cout << "Passenger Simulation Time: "
         << simulationTime
         << " ms"
         << endl;

    cout << "\n----- INTERPRETATION -----\n";

    if (total > 0)
    {
        double completionRate =
            completed * 100.0 / total;

        if (completionRate >= 80.0)
        {
            cout << "System Performance: GOOD"
                 << endl;
        }
        else if (completionRate >= 60.0)
        {
            cout << "System Performance: MODERATE"
                 << endl;
        }
        else
        {
            cout << "System Performance: NEEDS IMPROVEMENT"
                 << endl;
        }
    }
    else
    {
        cout << "System Performance: NO DATA"
             << endl;
    }

    cout << "\n======================================\n";
}
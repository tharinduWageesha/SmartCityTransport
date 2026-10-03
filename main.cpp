#include "Graph.h"
#include "BusNetwork.h"
#include "TrainNetwork.h"

int main()
{
    Graph city;

    BusNetwork busNetwork;

    TrainNetwork trainNetwork;


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
    // DISPLAY CITY
    // ======================================

    city.displayLocations();

    city.displayConnections();


    // ======================================
    // DISPLAY BUS NETWORK
    // ======================================

    busNetwork.displayBusRoutes(city);


    // ======================================
    // BUS SEARCH
    // ======================================

    cout << "\n===== BUS SEARCH =====\n";

    busNetwork.displayBusesAtStop(
        terminal
    );


    // ======================================
    // BUS ROUTE TEST
    // ======================================

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


    // ======================================
    // BUS SCHEDULE TEST
    // ======================================

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


    // ======================================
    // BUS PASSENGER TEST
    // ======================================

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


    // ======================================
    // DISPLAY TRAIN NETWORK
    // ======================================

    trainNetwork.displayTrainRoutes(
        city
    );


    // ======================================
    // TRAIN SEARCH
    // ======================================

    cout << "\n===== TRAIN SEARCH =====\n";


    trainNetwork.displayTrainsAtStation(
        station
    );


    // ======================================
    // TRAIN ROUTE TEST
    // ======================================

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


    // ======================================
    // TRAIN SCHEDULE TEST
    // ======================================

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


    // ======================================
    // TRAIN PASSENGER TEST
    // ======================================

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


    // ======================================
    // BFS ROUTE FINDING
    // ======================================

    cout << "\n===== ROUTE FINDING TEST =====\n";


    trainNetwork.findRouteBFS(
        city,
        home,
        mall
    );


    // ======================================
    // END
    // ======================================

    cout << "\n===== SYSTEM TEST COMPLETED =====\n";


    return 0;
}
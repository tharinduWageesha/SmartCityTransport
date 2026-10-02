#include "Graph.h"
#include "BusNetwork.h"

int main()
{
    Graph city;
    BusNetwork busNetwork;


    // =========================
    // CREATE CITY LOCATIONS
    // =========================

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


    // =========================
    // CREATE TRANSPORTATION
    // CONNECTIONS
    // =========================

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
        home,
        station,
        15,
        "Train"
    );

    city.addBidirectionalConnection(
        station,
        university,
        10,
        "Train"
    );

    city.addBidirectionalConnection(
        station,
        mall,
        8,
        "Train"
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


    // =========================
    // CREATE BUS ROUTES
    // =========================

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


    // =========================
    // DISPLAY LOCATIONS
    // =========================

    city.displayLocations();


    // =========================
    // DISPLAY CONNECTIONS
    // =========================

    city.displayConnections();


    // =========================
    // DISPLAY BUS NETWORK
    // =========================

    busNetwork.displayBusRoutes(city);


    // =========================
    // BUS SEARCH
    // =========================

    cout << "\n===== BUS SEARCH =====\n";

    busNetwork.displayBusesAtStop(
        terminal
    );


    // =========================
    // BUS ROUTE TEST
    // =========================

    cout << "\n===== BUS ROUTE TEST =====\n";

    cout << "Can travel from "
         << city.getLocationName(home)
         << " to "
         << city.getLocationName(university)
         << ": ";

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


    // =========================
    // BUS SCHEDULE TEST
    // =========================

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


    // =========================
    // PASSENGER BOARDING
    // =========================

    cout << "\n===== PASSENGER TEST =====\n";

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


    // =========================
    // AVAILABLE CAPACITY
    // =========================

    cout << "Available seats on Bus 101: "
         << busNetwork.getAvailableCapacity(0)
         << endl;


    // =========================
    // PASSENGERS LEAVING
    // =========================

    if (busNetwork.leavePassengers(
            0,
            5))
    {
        cout << "5 passengers left Bus 101."
             << endl;
    }
    else
    {
        cout << "Passengers could not leave Bus 101."
             << endl;
    }


    // =========================
    // FINAL BUS STATUS
    // =========================

    busNetwork.displayBusStatus();


    return 0;
}
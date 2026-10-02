
#include "Graph.h"

int main() {
    Graph city;

    int home = city.addLocation("Home");
    int terminal = city.addLocation("Bus Terminal");
    int station = city.addLocation("Railway Station");
    int university = city.addLocation("University");
    int hospital = city.addLocation("Hospital");
    int mall = city.addLocation("Shopping Mall");

    city.addBidirectionalConnection(
        home, terminal, 8, "Bus"
    );

    city.addBidirectionalConnection(
        terminal, university, 12, "Bus"
    );

    city.addBidirectionalConnection(
        terminal, hospital, 10, "Bus"
    );

    city.addBidirectionalConnection(
        home, station, 15, "Train"
    );

    city.addBidirectionalConnection(
        station, university, 10, "Train"
    );

    city.addBidirectionalConnection(
        station, mall, 8, "Train"
    );

    city.addBidirectionalConnection(
        university, mall, 7, "Bus"
    );

    city.addBidirectionalConnection(
        hospital, mall, 9, "Bus"
    );

    city.displayLocations();
    city.displayConnections();

    return 0;
}
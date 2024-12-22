#ifndef FLIGHT_H_INCLUDED
#define FLIGHT_H_INCLUDED

#define firstAirport(G) ((G).firstAirport)
#define nextAirport(A) ((A)->nextAirport)
#define firstRoute(A) ((A)->firstRoute)
#define airportID(A) ((A)->airportID)
#define destAirportID(R) ((R)->destAirportID)
#define flightTime(R) ((R)->flightTime)
#define nextRoute(R) ((R)->nextRoute)

#include <iostream>
#include <string>

using namespace std;

typedef struct airport *adrAirport;
typedef struct route *adrRoute;

struct airport {
    string airportID;
    adrAirport nextAirport;
    adrRoute firstRoute;
};

struct route {
    string destAirportID;
    int flightTime;
    adrRoute nextRoute;
};

struct flightNetwork {
    adrAirport firstAirport;
};

void createAirport(string newAirportID, adrAirport &a);
void initNetwork(flightNetwork &N);
void addAirport(flightNetwork &N, string newAirportID);
void addRoute(flightNetwork &N, string fromAirportID, string toAirportID, int flightTime);
void printNetwork(flightNetwork &N);

bool dfsRecursive(flightNetwork &N, adrAirport start, string destID, string visited[], int &visitCount, string path[], int &pathCount);
bool bfsIterative(flightNetwork &N, string startID, string destID, string visited[], int &visitCount, string path[], int &pathCount);

#endif // FLIGHT_H_INCLUDED

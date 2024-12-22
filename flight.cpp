#include "flight.h"

void createAirport(string newAirportID, adrAirport &a) {
    a = new airport;
    if (a != NULL) {
        airportID(a) = newAirportID;
        nextAirport(a) = NULL;
        firstRoute(a) = NULL;
    }
}

void initNetwork(flightNetwork &N) {
    firstAirport(N) = NULL;
}

void addAirport(flightNetwork &N, string newAirportID) {
    adrAirport newAirport, temp;
    createAirport(newAirportID, newAirport);

    if (firstAirport(N) == NULL) {
        firstAirport(N) = newAirport;
    } else {
        temp = firstAirport(N);
        while (nextAirport(temp) != NULL) {
            temp = nextAirport(temp);
        }
        nextAirport(temp) = newAirport;
    }
}

void addRoute(flightNetwork &N, string fromAirportID, string toAirportID, int flightTime) {
    adrAirport fromAirport = firstAirport(N);

    while (fromAirport != NULL && airportID(fromAirport) != fromAirportID) {
        fromAirport = nextAirport(fromAirport);
    }

    if (fromAirport != NULL) {
        adrRoute newRoute = new route;
        destAirportID(newRoute) = toAirportID;
        flightTime(newRoute) = flightTime;
        nextRoute(newRoute) = firstRoute(fromAirport);
        firstRoute(fromAirport) = newRoute;
    } else {
        cout << "Bandara " << fromAirportID << " tidak ditemukan." << endl;
    }
}

bool dfsRecursive(flightNetwork &N, adrAirport start, string destID, string visited[], int &visitCount, string path[], int &pathCount) {
    if (start == NULL) return false;

    visited[visitCount++] = airportID(start);
    path[pathCount++] = airportID(start);

    if (airportID(start) == destID) return true;

    adrRoute r = firstRoute(start);
    while (r != NULL) {
        adrAirport nextAirport = firstAirport(N);
        while (nextAirport != NULL && airportID(nextAirport) != destAirportID(r)) {
            nextAirport = nextAirport(nextAirport);
        }

        bool alreadyVisited = false;
        for (int i = 0; i < visitCount; i++) {
            if (visited[i] == destAirportID(r)) {
                alreadyVisited = true;
                break;
            }
        }

        if (!alreadyVisited && dfsRecursive(N, nextAirport, destID, visited, visitCount, path, pathCount)) {
            return true;
        }
        r = nextRoute(r);
    }

    --pathCount;
    return false;
}

bool bfsIterative(flightNetwork &N, string startID, string destID, string visited[], int &visitCount, string path[], int &pathCount) {
    adrAirport start = firstAirport(N);
    while (start != NULL && airportID(start) != startID) {
        start = nextAirport(start);
    }

    if (start == NULL) return false;

    string queue[100];
    int front = 0, rear = 0;

    queue[rear++] = startID;
    visited[visitCount++] = startID;

    while (front < rear) {
        string currentID = queue[front++];
        path[pathCount++] = currentID;

        if (currentID == destID) return true;

        adrAirport currentAirport = firstAirport(N);
        while (currentAirport != NULL && airportID(currentAirport) != currentID) {
            currentAirport = nextAirport(currentAirport);
        }

        if (currentAirport != NULL) {
            adrRoute r = firstRoute(currentAirport);
            while (r != NULL) {
                bool alreadyVisited = false;
                for (int i = 0; i < visitCount; i++) {
                    if (visited[i] == destAirportID(r)) {
                        alreadyVisited = true;
                        break;
                    }
                }

                if (!alreadyVisited) {
                    queue[rear++] = destAirportID(r);
                    visited[visitCount++] = destAirportID(r);
                }
                r = nextRoute(r);
            }
        }
    }

    return false;
}

void printNetwork(flightNetwork &N) {
    adrAirport a = firstAirport(N);
    while (a != NULL) {
        cout << airportID(a) << " ->";
        adrRoute r = firstRoute(a);
        while (r != NULL) {
            cout << " (" << destAirportID(r) << ", " << flightTime(r) << " mins)";
            r = nextRoute(r);
        }
        cout << endl;
        a = nextAirport(a);
    }
}

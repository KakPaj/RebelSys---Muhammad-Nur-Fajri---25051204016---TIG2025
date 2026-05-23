#include <iostream>
using namespace std;

struct Planet;

struct routeEdge
{
    int distance;
    Planet* destination;
    routeEdge* next;
};

struct Planet
{
    string planetName;

    routeEdge* headRoute;
    Planet& nextPlanet;
};

void discoverPlanet()
{
    
}

void addHyperspaceRoute()
{

}

void displayMap()
{

}

void findSafeRoute()
{

}


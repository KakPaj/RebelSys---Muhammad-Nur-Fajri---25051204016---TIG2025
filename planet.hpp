#pragma once
#include <iostream>
#include <string>
#include "input.hpp"
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
    bool visited; 
    routeEdge* headRoute; 
    Planet* nextPlanet;   
};

Planet* mapRoot = NULL; 

Planet* searchPlanet(string name)
{
    Planet* temp = mapRoot;
    while (temp != NULL)
    {
        if (temp -> planetName == name) return temp;
        temp = temp -> nextPlanet;
    }
    return NULL;
}

void discoverPlanet()
{
    system("cls");
    cout << "=========================================" << endl
         << "         [ DISCOVER NEW PLANET ]         " << endl
         << "=========================================" << endl;

    string name = inputString(" Enter Planet Name: ");

    if (searchPlanet(name) != NULL)
    {
        cout << "[-] Planet " << name << " is already recorded in the Galaxy Map." << endl;
        system("pause");
        return;
    }

    Planet* newPlanet = new Planet();
    newPlanet -> planetName = name;
    newPlanet -> visited = false;
    newPlanet -> headRoute = NULL;
    newPlanet -> nextPlanet = NULL;

    if (mapRoot == NULL)
    {
        mapRoot = newPlanet;
    }
    else
    {
        Planet* temp = mapRoot;
        while (temp -> nextPlanet != NULL)
        {
            temp = temp -> nextPlanet;
        }
        temp -> nextPlanet = newPlanet;
    }

    cout << "[+] Planet " << name << " has been added to the Galaxy Map!" << endl;
    system("pause");
}

void addHyperspaceRoute()
{
    system("cls");
    cout << "=========================================" << endl
         << "      [ CHART HYPERSPACE ROUTE ]         " << endl
         << "=========================================" << endl;

    if (mapRoot == NULL || mapRoot -> nextPlanet == NULL)
    {
        cout << "[-] Need at least 2 planets to create a route!" << endl;
        system("pause");
        return;
    }

    string origin = inputString(" Origin Planet      : ");
    string dest = inputString(" Destination Planet : ");
    int dist = inputInt(" Jump Distance (Ly) : ");

    Planet* pOrigin = searchPlanet(origin);
    Planet* pDest = searchPlanet(dest);

    if (pOrigin == NULL || pDest == NULL || pOrigin == pDest)
    {
        cout << "[-] Invalid coordinates or trying to link a planet to itself!" << endl;
        system("pause");
        return;
    }

    routeEdge* route1 = new routeEdge();
    route1 -> distance = dist;
    route1 -> destination = pDest;
    route1 -> next = pOrigin -> headRoute;
    pOrigin -> headRoute = route1;

    routeEdge* route2 = new routeEdge();
    route2 -> distance = dist;
    route2 -> destination = pOrigin;
    route2 -> next = pDest -> headRoute;
    pDest -> headRoute = route2;

    cout << "[+] Hyperspace lane charted successfully!" << endl;
    system("pause");
}

void displayMap()
{
    system("cls");
    cout << "=========================================" << endl;
    cout << "          [ GALAXY MAP ROUTES ]          " << endl;
    cout << "=========================================" << endl;

    if (mapRoot == NULL)
    {
        cout << "[-] The galaxy map is completely empty." << endl;
        system("pause");
        return;
    }

    Planet* temp = mapRoot;
    while (temp != NULL)
    {
        cout << "[O] " << temp -> planetName << " connects to:" << endl;
        
        routeEdge* rTemp = temp -> headRoute;
        if (rTemp == NULL) cout << "     ->  (No lanes charted)" << endl;
        
        while (rTemp != NULL)
        {
            cout << "    => " << rTemp -> destination -> planetName 
                 << " (" << rTemp -> distance << " Lightyears)" << endl;
            rTemp = rTemp -> next;
        }
        cout << "-----------------------------------------" << endl;
        temp = temp -> nextPlanet; 
    }
    system("pause");
}

void resetVisited()
{
    Planet* temp = mapRoot;
    while (temp != NULL)
    {
        temp -> visited = false;
        temp = temp -> nextPlanet;
    }
}

bool initFindRoute(Planet* current, Planet* target, int currentDist, int& finalDist)
{
    if (current == target)
    {
        finalDist = currentDist;
        return true;
    }

    current -> visited = true;

    routeEdge* edge = current -> headRoute;
    while (edge != NULL)
    {
        if (!edge -> destination -> visited)
        {
            if (initFindRoute(edge -> destination, target, currentDist + edge -> distance, finalDist))
            {
                cout << "    <- " << current -> planetName;
                return true;
            }
        }
        edge = edge -> next;
    }
    return false;
}

void displaySafeRoute()
{
    system("cls");
    cout << "=========================================" << endl
         << "         [ NAVI-COMPUTER SEARCH ]        " << endl
         << "=========================================" << endl;

    string origin = inputString("Starting Planet: ");
    string dest = inputString("Destination Planet: ");

    Planet* pOrigin = searchPlanet(origin);
    Planet* pDest = searchPlanet(dest);

    if (pOrigin == NULL || pDest == NULL)
    {
        cout << "[-] Coordinates invalid. Planets not found." << endl;
        system("pause");
        return;
    }

    resetVisited(); 
    int totalDistance = 0;

    cout << "\n Calculating hyperspace jumps..." << endl;
    cout << " Route: " << pDest -> planetName; 

    if (initFindRoute(pOrigin, pDest, 0, totalDistance))
    {
        cout << "\n\n [+] Safe Route Found!" << endl;
        cout << " [+] Total Distance: " << totalDistance << " Lightyears" << endl;
    }
    else
    {
        cout << "\n\n [-] NO SAFE ROUTE EXISTS between these planets!" << endl;
    }
    system("pause");
}

void mappingMenu()
{
    bool back = false;
    while (!back)
    {
        system("cls");
        cout << "=========================================" << endl
            << "              [ GALAXY NAV ]             " << endl
            << "=========================================" << endl
            << "1. Discover New Planet" << endl << endl
            << "2. Chart Hyperspace Route" << endl << endl
            << "3. View Galaxy Map" << endl << endl
            << "4. Navi-Computer"  << endl << endl
            << "5. Return to Command Center" << endl << endl
            << "=========================================" << endl;
        int opt = inputInt("[-] Choice: ");
        if (opt == 1) 
        {
            discoverPlanet();
        }
        else if (opt == 2)
        {
            addHyperspaceRoute();
        }
        else if (opt == 3)
        {
            displayMap;
        }
        else if (opt == 4)
        {
            displaySafeRoute();
        }
        else if (opt == 5)
        {
            back = true;
        }
    }
}
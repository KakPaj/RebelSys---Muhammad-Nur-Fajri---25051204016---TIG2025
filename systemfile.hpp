#include <iostream>
#include <fstream>
#include <string>
#include "crew.hpp"
#include "spaceship.hpp"
#include "missions.hpp"
#include "planet.hpp"
using namespace std;

int splitString(string input, string output[], char divider)
{
    int count = 0;
    string temp = "";
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == divider)
        {
            output[count++] = temp;
            temp = "";
        }
        else
        {
            temp += input[i];
        }
    }
    if (temp != "")
    {
        output[count++] = temp;
    }
    return count;
}

void saveCrewRec(Crew* node, ofstream& file)
{
    if (node == NULL) return;

    file << node -> crewName << "|" 
         << node -> rankName << "|" 
         << node -> rankNum << "|" 
         << node -> status << "|"
         << (node -> homeShip ? node -> homeShip -> callSign : "NONE") << endl;

    saveCrewRec(node -> left, file);
    saveCrewRec(node -> right, file);
}

void saveCrew()
{
    ofstream file("crew_data.txt");
    if (!file.is_open()) return;

    saveCrewRec(RootCR, file);
    file.close();
}

void loadCrew()
{
    ifstream file("crew_data.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        string data[4];
        splitString(line, data, '|');

        Crew* newCrew = new Crew();
        newCrew -> crewName = data[0];
        newCrew -> rankName = data[1];
        newCrew -> rankNum = stoi(data[2]);
        newCrew -> status = stoi(data[3]);
        newCrew -> left = NULL;
        newCrew -> right = NULL;
        newCrew -> next = NULL;

        string shipCall = data[4];
        if (shipCall != "NONE")
        {
            for (int i = 0; i < HANGAR; i++)
            {
                if (hangarDock[i] != NULL)
                {
                    Spaceship* found = searchShip(hangarDock[i] -> headShip, shipCall);
                    if (found != NULL)
                    {
                        newCrew -> homeShip = found;

                        newCrew -> next = found -> headCrew; 
                        found -> headCrew = newCrew;
                        break;
                    }
                }
            }
        }

        RootCR = insertCrew(RootCR, newCrew);
    }
    file.close();
}

void saveSpaceships()
{
    ofstream file("ship_data.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < 15; i++)
    {
        Squadron* s = hangarDock[i];
        if (s == NULL) continue;

        Spaceship* temp = s -> headShip;
        while (temp != NULL)
        {
            file << s -> squadName << "|" 
                 << temp -> callSign << "|" 
                 << temp -> nameShip << endl;
            temp = temp -> next;
        }
    }
    file.close();
}

void loadSpaceships()
{
    ifstream file("ship_data.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        string data[3];
        splitString(line, data, '|');

        Squadron* s = searchSquadron(hangarDock, data[0]);
        if (s == NULL) continue;

        Spaceship* newShip = new Spaceship();
        s -> squadName = data[0];
        newShip -> callSign = data[1];
        newShip -> nameShip = data[2];
        newShip -> headCrew = NULL;
        newShip -> next = NULL;

        if (s -> headShip == NULL)
        {
            s -> headShip = newShip;
        }
        else
        {
            Spaceship* temp = s -> headShip;
            while (temp -> next != NULL) temp = temp -> next;
            temp -> next = newShip;
        }
    }
    file.close();
}

void saveMissionsRec(Missions* node, ofstream& file)
{
    if (node == NULL) return;

    file << node -> missionID << "|" 
         << node -> missionName << "|" 
         << node -> missionLevel << "|" 
         << node -> targetPlanet << "|" 
         << node -> daysLeft << "|" 
         << node -> endStatus << "|" 
         << node -> squadron << "|" 
         << (node -> deployedShip ? node -> deployedShip -> callSign : "NONE") << endl;

    saveMissionsRec(node -> left, file);
    saveMissionsRec(node -> right, file);
}

void saveMissions()
{
    ofstream file("mission_data.txt");
    if (!file.is_open()) return;
    saveMissionsRec(RootMS, file);
    file.close();
}

void rebuildMissionStructures(Missions* node)
{
    if (node == NULL) return;

    if (node -> endStatus == "On-Going")
    {
        if (activeQueueFront == NULL) { activeQueueFront = node; activeQueueRear = node; }
        else { activeQueueRear -> next = node; activeQueueRear = node; }
        node -> next = NULL;
    }
    else if (node -> endStatus == "SUCCESS" || node -> endStatus == "FAILED")
    {
        node -> next = missionLogStackTop;
        missionLogStackTop = node;
    }

    rebuildMissionStructures(node -> left);
    rebuildMissionStructures(node -> right);
}

void loadMissions()
{
    ifstream file("mission_data.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        string data[8];
        splitString(line, data, '|');

        Missions* m = new Missions();
        m -> missionID = stoi(data[0]);
        m -> missionName = data[1];
        m -> missionLevel = stoi(data[2]);
        m -> targetPlanet = data[3];
        m -> daysLeft = stoi(data[4]);
        m -> endStatus = data[5];
        m -> squadron = data[6];
        
        // Link Ship
        string shipCall = data[7];
        m -> deployedShip = NULL;
        if (shipCall != "NONE") {
            Squadron* s = searchSquadron(hangarDock, m -> squadron);
            if (s) m -> deployedShip = searchShip(s -> headShip, shipCall);
        }

        m -> left = m -> right = m -> next = NULL;
        RootMS = insertMission(RootMS, m);
    }
    file.close();
    
    rebuildMissionStructures(RootMS);
}

void savePlanetSystem()
{
    ofstream pFile("planets.txt");
    Planet* temp = mapRoot;
    while (temp != NULL)
    {
        pFile << temp -> planetName << endl;
        temp = temp -> nextPlanet;
    }
    pFile.close();

    ofstream rFile("routes.txt");
    temp = mapRoot;
    while (temp != NULL)
    {
        routeEdge* edge = temp -> headRoute;
        while (edge != NULL)
        {
            if (temp -> planetName < edge -> destination -> planetName)
            {
                rFile << temp -> planetName << "|" << edge -> destination -> planetName << "|" << edge -> distance << endl;
            }
            edge = edge -> next;
        }
        temp = temp -> nextPlanet;
    }
    rFile.close();
}

void loadPlanetSystem()
{
    ifstream pFile("planets.txt");
    string line;
    while (getline(pFile, line))
    {
        if (line.empty()) continue;
        Planet* newPlanet = new Planet();
        newPlanet->planetName = line;
        newPlanet->visited = false;
        newPlanet->headRoute = NULL;
        newPlanet->nextPlanet = NULL;
        if (mapRoot == NULL) mapRoot = newPlanet;
        else {
            Planet* temp = mapRoot;
            while (temp -> nextPlanet != NULL) temp = temp -> nextPlanet;
            temp -> nextPlanet = newPlanet;
        }
    }
    pFile.close();

    ifstream rFile("routes.txt");
    while (getline(rFile, line))
    {
        if (line.empty()) continue;
        string data[3];
        splitString(line, data, '|');
        Planet* p1 = searchPlanet(data[0]);
        Planet* p2 = searchPlanet(data[1]);
        int dist = stoi(data[2]);
        if (p1 && p2)
        {
            routeEdge* route1 = new routeEdge{dist, p2, p1 -> headRoute};
            p1 -> headRoute = route1;
            routeEdge* route2 = new routeEdge{dist, p1, p2 -> headRoute};
            p2 -> headRoute = route2;
        }
    }
    rFile.close();
}
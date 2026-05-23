#include <iostream>
using namespace std;

struct Missions
{
    int missionID;
    string missionName;
    int missionLevel;
    string targetPlanet;
    int daysLeft;
    string endStatus;
    Missions* left;
    Missions* right;

    Missions* next;
};

Missions* Root = NULL;

Missions* insertMission()
{

}

Missions* deleteMission()
{

}

void displayMissionsBoard()
{

}

void startMission()
{

}

void finishMission()
{

}

void activeMission()
{

}

void missionLog()
{

}

void dayPass()
{

}


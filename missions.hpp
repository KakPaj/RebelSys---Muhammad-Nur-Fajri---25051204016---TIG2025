#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Spaceship;
struct Squadron;

struct Missions
{
    int missionID;
    string missionName;
    int missionLevel;
    string targetPlanet;
    int daysLeft;
    string endStatus;
    string squadron;
    
    Missions* left;
    Missions* right;

    Spaceship* deployedShip;

    Missions* next;
};

#include "input.hpp"
#include "planet.hpp"
#include "spaceship.hpp"
#include "squadron.hpp"

Missions* RootMS = NULL;
Missions* activeQueueFront = NULL;
Missions* activeQueueRear = NULL;
Missions* missionLogStackTop = NULL;

Missions* insertMission(Missions* root, Missions* newMission)
{
    if (root == NULL) return newMission;

    if (newMission -> missionLevel < root -> missionLevel)
    {
        root -> left = insertMission(root -> left, newMission);
    }
    else if (newMission -> missionLevel > root -> missionLevel)
    {
        root -> right = insertMission(root -> right, newMission);
    }
    else
    {
        if (newMission -> missionName < root -> missionName)
        {
            root -> left = insertMission(root -> left, newMission);
        }
        else if (newMission -> missionName > root -> missionName)
        {
            root -> right = insertMission(root -> right, newMission);
        }
        else
        {
            cout << "[-] Error: Mission already exist. Access terminated. . ." << endl;
            system("pause");
        }
    }
    return root;
}

void addMission()
{
    system("cls");
    cout << "=========================================" << endl
         << "            [ ADD NEW MISSION ]          " << endl
         << "=========================================" << endl;

    int id = inputInt("\nMission ID: ");
    string name = inputString("\nMission Name: ");
    int level = inputInt("\nMission Level: ");
    
    string planet = inputString("\nTarget Planet: ");
    if (searchPlanet(planet) == NULL)
    {
        cout << "\n[-] ERROR: Planet '" << planet << "' is not charted in the Galaxy Map!" << endl;
        system("pause");
        return;
    }

    int days = inputInt("\nDays to Complete: ");

    Missions* newMission = new Missions();
    newMission -> missionID = id;
    newMission -> missionName = name;
    newMission -> missionLevel = level;
    newMission -> targetPlanet = planet;
    newMission -> daysLeft = days;
    newMission -> endStatus = "Available";

    newMission -> deployedShip = NULL;
    newMission -> left = NULL;
    newMission -> right = NULL;
    newMission -> next = NULL;

    RootMS = insertMission(RootMS, newMission);

    cout << endl << "=========================================" << endl;
    cout << "[+] Mission '" << newMission -> missionName << "' has been added to Mission Board!" << endl;
    system("pause");
}

void displayMissionsBoard(Missions* root)
{
    if (root != NULL)
    {
        displayMissionsBoard(root -> left);

        Missions* temp = root;
        while (temp != NULL)
        {
            cout << "ID: " << temp -> missionID << " | Level: " << temp -> missionLevel
                 << " | " << temp -> missionName << " (" << temp -> targetPlanet << ") | "
                 << temp -> daysLeft << " Days | Status: " << temp -> endStatus << endl;
            temp = temp -> next;
        }

        displayMissionsBoard(root -> right);
    }
}

void initMissionBoard()
{
    system("cls");
    cout << "=========================================" << endl
         << "         [ AVAILABLE MISSIONS ]          " << endl
         << "=========================================" << endl;
            
    if (Root == NULL) 
    {
        cout << "[-] No missions posted on the board yet." << endl;
    }
    else 
    {
        displayMissionsBoard(RootMS);
    }
            
    cout << "=========================================" << endl;
    system("pause");
}

Missions* searchMissions(Missions* root, int level, int id)
{
    if (root == NULL) return NULL;
    
    if (root->missionLevel == level && root->missionID == id) return root;

    if (level < root->missionLevel) return searchMissions(root->left, level, id);
    
    if (level > root->missionLevel) return searchMissions(root->right, level, id);

    Missions* foundLeft = searchMissions(root->left, level, id);
    if (foundLeft != NULL) return foundLeft;
    
    return searchMissions(root->right, level, id);
}

void startMission(int level, int id, string squad, Spaceship* ship)
{
    Missions* targMission = searchMissions(RootMS, level, id);

    if (targMission == NULL)
    {
        cout << "[-] Mission not found. Access terminated. . ." << endl;
        system("pause");
        return;
    }

    if (targMission -> endStatus != "Available")
    {
        cout << "[-] Mission has been taken or finished. Access terminated. . ." << endl;
        system("pause");
        return;
    }

    if (ship == NULL || ship -> headCrew == NULL)
    {
        cout << "[-] Ship or crew invalid. Deployment terminated. . ." << endl;
        system("pause");
        return;
    }

    string basePlanetName = inputString("Fleet Current Location (Base): ");
    Planet* pBase = searchPlanet(basePlanetName);
    Planet* pTarget = searchPlanet(targMission -> targetPlanet);

    if (pBase == NULL)
    {
        cout << "[-] Base location '" << basePlanetName << "' is not in the Galaxy Map!" << endl;
        system("pause");
        return;
    }

    resetVisited();
    int travelDistance = 0;

    cout << "\n[!] Navi-Computer calculating jump vectors..." << endl;
    cout << "Route: " << pTarget -> planetName;

    if (!initFindRoute(pBase, pTarget, 0, travelDistance))
    {
        cout << "\n\n[-] DEPLOYMENT ABORTED!" << endl;
        cout << "[-] No safe hyperspace route exists from " << basePlanetName << " to " << targMission -> targetPlanet << "!" << endl;
        system("pause");
        return;
    }

    cout << "\n\n[+] Safe Route Plotted! Total Jump Distance: " << travelDistance << " Lightyears." << endl;
    cout << "[+] Cleared for deployment sequence.\n" << endl;

    Crew* temp = ship -> headCrew;
    while (temp != NULL)
    {
        temp -> status = 2;
        temp = temp -> next;
    }

    targMission -> deployedShip = ship;
    targMission -> endStatus = "On-Going";
    targMission -> next = NULL;

    if (activeQueueFront == NULL)
    {
        activeQueueFront = targMission;
        activeQueueRear = targMission;
    }
    else
    {
        activeQueueRear -> next = targMission;
        activeQueueRear = targMission;
    }

    cout << "[+] " << ship -> callSign << " deployed for mission: " << targMission -> missionName << endl;
    system("pause");
}

void displayStartMission()
{
    system("cls");
    cout << endl << "=========================================" << endl
                 << "         [ DEPLOY FOR MISSION ]          " << endl
                 << "=========================================" << endl;

    int id = inputInt("Target Mission ID: ");
    int level = inputInt("Target Mission Level: ");
    string squad = inputString("Squadron: ");
    string ship = inputString("Deploy: Ship ");

    Squadron* squadTargeted = searchSquadron(hangarDock, squad);
    if (squadTargeted == NULL)
    {
        cout << "[-] Squadron " << squad << " not found. Access Terminated. . ." << endl;
        system("pause");
        return;
    }

    Spaceship* shipTargeted = searchShip(squadTargeted -> headShip, ship);
    if (shipTargeted == NULL)
    {
        cout << "[-] Ship " << ship << " not found. Access Terminated. . ." << endl;
        system("pause");
        return;   
    }
    
    startMission(level, id, squad, shipTargeted);
}

void finishMission(Missions* targMission)
{
    Spaceship* ship = targMission -> deployedShip;
    int totalPower = 0;

    Crew* temp = ship -> headCrew;
    while (temp != NULL)
    {
        totalPower += temp -> rankNum;
        temp = temp -> next;
    }

    srand(time(0));
    int luck = (rand() % 100) + 1;
    int finalScore = totalPower + luck;

    cout << endl << "=========================================" << endl
                 << "        [ MISSION RESULT REPORT ]        " << endl
                 << "=========================================" << endl << endl;
    cout << " Target: " << targMission -> targetPlanet << " (Lvl " << targMission -> missionLevel << ")" << endl;
    cout << " Combat Score: " << finalScore << endl;

    if (finalScore >= (targMission -> missionLevel * 15))
    {
        targMission -> endStatus = "SUCCESS";
        cout << "[+] MISSION ACCOMPLISHED!" << endl;
        
        while (ship -> headCrew != NULL)
        {
            Crew* aliveCrew = ship -> headCrew;
            unassignKillCrew(ship, aliveCrew, 0);
        }
    }
    else
    {
        targMission -> endStatus = "FAILED";
        cout << "[-] TOTAL DEFEAT. SHIP DESTROYED." << endl;
        
        while (ship -> headCrew != NULL)
        {
            Crew* deadCrew = ship -> headCrew;
            unassignKillCrew(ship, deadCrew, 3);
        }
        Squadron* squad = searchSquadron(hangarDock, targMission -> squadron);
        destroyShip(squad, ship);
    }
    cout << "=========================================\n" << endl;

    targMission -> deployedShip = NULL;

    targMission -> next = missionLogStackTop;
    missionLogStackTop = targMission;
}

void dayPass()
{
    system("cls");
    cout << "=========================================" << endl
         << "   [ TIME JUMP: ONE CYCLE HAS PASSED ]   " << endl
         << "=========================================" << endl << endl;

    if (activeQueueFront == NULL)
    {
        cout << "[!] No active missions currently deployed." << endl;
        system("pause");
        return;
    }

    Missions* curr = activeQueueFront;
    Missions* prev = NULL;

    while (curr != NULL)
    {
        curr -> daysLeft -= 1;

        if (curr -> daysLeft <= 0)
        {
            Missions* finishedTask = curr;

            if (prev == NULL)
            {
                activeQueueFront = curr -> next;
                curr = activeQueueFront;
                if (activeQueueFront == NULL) activeQueueRear = NULL;
            }
            else
            {
                prev -> next = curr -> next;
                curr = curr -> next;
                if (curr == NULL) activeQueueRear = prev;
            }

            finishMission(finishedTask);
        }
        else
        {
            prev = curr;
            curr = curr -> next;
        }
    }
    system("pause");
}

void activeMission()
{
    system("cls");
    cout << "=========================================" << endl
         << " 	        [ DEPLOYED FLEETS ] 	      " << endl
         << "=========================================" << endl << endl;

    if (activeQueueFront == NULL) cout << "[-] No fleets are currently deployed." << endl;

    Missions* temp = activeQueueFront;
    while (temp != NULL)
    {
        cout << "> " << temp -> deployedShip -> callSign << " is infiltrating " 
             << temp -> targetPlanet << " | " << temp -> daysLeft << " Days remaining." << endl;
        temp = temp -> next;
    }
    system("pause");
}

void missionLog()
{
    system("cls");
    cout << "=========================================" << endl
         << " 	       [ MISSION HISTORY LOG ] 	      " << endl
         << "=========================================" << endl << endl;

    if (missionLogStackTop == NULL) cout << "[-] No missions have been concluded yet." << endl;

    Missions* temp = missionLogStackTop;
    while (temp != NULL)
    {
        cout << "> " << temp -> missionName << " (" << temp -> targetPlanet << ") - " 
             << temp -> endStatus << endl;
        temp = temp -> next;
    }
    system("pause");
}

void missionMenu()
{
    bool back = false;
    while (!back)
    {
        system("cls");
        cout << "=========================================" << endl
            << "           [ MISSION TERMINAL ]          " << endl
            << "=========================================" << endl
            << "1. New Mission" << endl << endl
            << "2. Mission Board" << endl << endl
            << "3. Deploy Fleet" << endl << endl
            << "4. Active Deployed Fleet" << endl << endl
            << "5. Mission Log" << endl << endl
            << "6. Return to Command Center" << endl << endl
            << "=========================================" << endl;
        int opt = inputInt("[-] Choice: ");
        if (opt == 1) 
        {
            addMission();
        }
        else if (opt == 2)
        {
            initMissionBoard();
        }
        else if (opt == 3)
        {
            displayStartMission();
        }
        else if (opt == 4)
        {
            activeMission();
        }
        else if (opt == 5)
        {
            missionLog();
        }
        else if (opt == 6)
        {
            back = true;
        }
    }
}
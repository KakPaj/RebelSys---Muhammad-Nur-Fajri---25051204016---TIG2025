#pragma once
#include <iostream>
using namespace std;

struct Spaceship
{
    string callSign;
    string nameShip;

    Crew* headCrew;

    Spaceship* next;
};

#include "crew.hpp"
#include "squadron.hpp"

void assignShip(Squadron* hangarDock[], string squadTarget, string cSign, string nameShip)
{
    Squadron* squadron = searchSquadron(hangarDock, squadTarget);

    if (squadTarget == "")
    {
        cout << "[-] Invalid Squadron. Access Terminated. . .";
        system("pause");
        return;
    }

    Spaceship* newShip = new Spaceship();
    newShip -> callSign = cSign;
    newShip -> nameShip = nameShip;
    newShip -> headCrew = NULL;

    newShip -> next = squadron -> headShip;
    squadron -> headShip = newShip;

    cout << "[+] " << cSign << " has joined with " << squadron -> squadName << endl
         << "=========================================" << endl;
}

void initiateAssignShip()
{
    system("cls");
    cout << "=========================================" << endl
         << "         [ NEW SHIP ASSIGNMENT ]         " << endl
         << "=========================================" << endl;
    string nameShip = inputString("Ship Model: ");
    string cSign = inputString("Callsign: ");
    string squadTarget = inputString("Assign to: Squadron ");
    assignShip(hangarDock, squadTarget, cSign, nameShip);
    system("pause");
}

Spaceship* searchShip (Spaceship* headShip, string callSign)
{
    Spaceship* temp = headShip;
    while (temp != NULL)
    {
        if (temp -> callSign == callSign) return temp;
        else temp = temp -> next;
    }
    return NULL;
}

void displayFleet(Spaceship* headShip, string squadName)
{
    system("cls");
    cout << "=========================================" << endl
         << "         [ HANGAR FLEET MONITOR ]        " << endl
         << "=========================================" << endl
         << "[ " << squadName << " Squadron ]";

    if (headShip == NULL)
    {
        cout << "[-] Squadron empty. Access Terminated. . ." << endl;
        system("pause");
        return;
    }

    Spaceship* temp = headShip;
    int numbering = 1;

    while (temp != NULL)
    {
        cout << numbering << ". " << "Callsign: " << temp -> callSign << " - " << "Model: " << temp -> nameShip << endl;
        temp = temp -> next;
        numbering++;
    }
    cout << "=========================================" << endl;
    system("pause");
    return;
}

void initiateDisplayFleet()
{
    system("cls");
    cout << "=========================================" << endl
         << "             [ FLEET MONITOR ]           " << endl
         << "=========================================" << endl;
    cout << "1. Phoenix" << "   " << "2. Phantom" << endl << "3. Rogue-One" << "    " << "4. Gold" << endl 
         << "5. Red" << "    " << "6. Green" << endl << "7. Blue" << "    " << "8. Grey" << endl << "9. Nova" << "    "
         << "10. Corona" << endl << "11. Hound" << "    " << "12. Vanguard" << endl << "13. Wraith" << "    " << "14. Saber" << endl << "15. Blade" << endl
         << "=========================================" << endl;
    string squad = inputString("Squadron: ");
    Squadron* squadTarget = searchSquadron(hangarDock, squad);
    if (squadTarget != NULL) displayFleet(squadTarget -> headShip, squad);
}

void assignCrewtoShip(Spaceship* ship, Crew* crew)
{
    if (crew -> status != 0 || crew -> homeShip != NULL)
    {
        cout << "[-] Crew " << crew -> crewName << " has already been assigned. Access Terminated. . .";
        system("pause");
        return;   
    }
    crew -> status = 1;
    crew -> homeShip = ship;
    crew -> next = ship -> headCrew;
    ship -> headCrew = crew;

    cout << "[+] Crew " << crew -> crewName << " has been assigned to " << ship -> callSign << endl
         << "=========================================" << endl;
    system("pause");
    return;
}

void displayCrewtoShip()
{
    system("cls");
    cout << "=========================================" << endl
         << "            [ CREW ASSIGNMENT ]          " << endl
         << "=========================================" << endl << endl;
    string squad = inputString("Squadron: ");
    string ship = inputString("\n\nCallsign: ");
    string name = inputString("\n\nCrew Name: ");
    int rank = rankDecode("\n\nRank: ");
    cout << endl << endl << "=========================================" << endl;

    Squadron* squadTargeted = searchSquadron(hangarDock, squad);
    if (squadTargeted == NULL)
    {
        cout << "[-] Squadron " << squad << " not found. Access Terminated. . .";
        system("pause");
        return;
    }

    Spaceship* shipTargeted = searchShip(squadTargeted -> headShip, ship);
    if (shipTargeted == NULL)
    {
        cout << "[-] Ship " << ship << " not found. Access Terminated. . .";
        system("pause");
        return;   
    }

    Crew* crewTargeted = searchCrew(Root, name, rank);
    if (crewTargeted == NULL)
    {
        cout << "[-] Crew " << name << " not found. Access Terminated. . .";
        system("pause");
        return;     
    }
    cout << "[-] Processing assignment. . .";
    system("pause");
    assignCrewtoShip(shipTargeted, crewTargeted);
    return;
}

void displayCrewinShip(Spaceship* ship)
{
    if (ship == NULL)
    {
        cout << "[-] Invalid ship. Access terminated. . ." << endl;
        system("pause");
        return;
    }

    system("cls");
    cout << "=========================================" << endl
         << "         [ " << ship -> callSign << " CREW LIST ]        " << endl
         << "=========================================" << endl;

    if (ship -> headCrew == NULL)
    {
        cout << "[-] " << ship -> callSign << " has no crew(s). Access terminated. . ." << endl
             << "=========================================" << endl;
        system("pause");
        return;
    }

    Crew* temp = ship -> headCrew;
    int numbering = 1;

    while (temp != NULL)
    {
        cout << numbering << ". " << temp -> crewName << " - " << temp -> rankName << endl;
        temp = temp -> next;
        numbering++;
    }

    cout << endl << endl << "=========================================" << endl;
    system("pause");
    return;
}

void initiateDisplayCrewinShip()
{
    system("cls");
    cout << "=========================================" << endl
         << "           [ SHIP CREWS MONITOR ]        " << endl
         << "=========================================" << endl << endl;
    string squad = inputString("Squadron: ");
    string ship = inputString("\n\nCallsign: ");

    cout << endl << endl << "=========================================" << endl;

    Squadron* squadTargeted = searchSquadron(hangarDock, squad);
    if (squadTargeted == NULL)
    {
        cout << "[-] Squadron " << squad << " not found. Access Terminated. . .";
        system("pause");
        return;
    }

    Spaceship* shipTargeted = searchShip(squadTargeted -> headShip, ship);
    if (shipTargeted == NULL)
    {
        cout << "[-] Ship " << ship << " not found. Access Terminated. . .";
        system("pause");
        return;   
    }

    cout << "[-] Processing unit search. . .";
    system("pause");
    displayCrewinShip(shipTargeted);
    return;
}

void unassignKillCrew(Spaceship* ship, Crew* crew, int status)
{
    if (ship == NULL || crew == NULL)
    {
        cout << "[-] Invalid data. Access terminated. . ." << endl;
        system("pause");
        return;
    }

    if (crew -> homeShip != ship)
    {
        cout << "[-] " << crew -> crewName << " is not assigned in " << ship -> callSign << " Access terminated. . ." << endl;
        system("pause");
        return;
    }

    if (ship -> headCrew == crew)
    {
        ship -> headCrew = crew -> next;

    }
    else
    {
        Crew* prev = ship -> headCrew;

        while (prev != NULL && prev -> next != crew)
        {
            prev = prev -> next;
        }

        if (prev != NULL)
        {
            prev -> next = crew -> next;
        }
    }

    crew -> next = NULL;
    crew -> homeShip = NULL;
    crew -> status = status;

    if (status == 0) cout << "[+] " << crew -> crewName << " succesfully unassigned from " << ship -> callSign << endl;
    else if (status == 3) cout << "[-] " << crew -> crewName << " deceased in action. . ." << endl;
    
    return;
}

void fleetMenu()
{
    system("cls");
    cout << "=========================================" << endl
         << "              [ FLEET MENU ]             " << endl
         << "=========================================" << endl
         << "1. New Ship" << endl << endl
         << "2. Fleet Monitor" << endl << endl
         << "3. Assign Crew to Ship" << endl << endl
         << "4. Ship Crew(s) Info"  << endl << endl
         << "=========================================" << endl;
    int opt = inputInt("[-] Choice: ");
    if (opt == 1) 
    {
        initiateAssignShip();
    }
    else if (opt == 2)
    {
        initiateDisplayFleet();
    }
    else if (opt == 3)
    {
        displayCrewtoShip();
    }
    else if (opt == 4)
    {
        initiateDisplayCrewinShip();
    }
}
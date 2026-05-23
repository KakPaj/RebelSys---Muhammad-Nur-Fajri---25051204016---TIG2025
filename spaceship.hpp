#pragma once
#include <iostream>
#include "crew.hpp"
#include "squadron.hpp"
using namespace std;

struct Spaceship
{
    string callSign;
    string nameShip;

    Crew* rootCrew;

    Spaceship* next;
};

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
    newShip -> rootCrew = NULL;

    newShip -> next = squadron -> headShip;
    squadron -> headShip = newShip;

    cout << "[+] " << cSign << " has joined with " << squadron << endl
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
         << "         [ HANGAR FLEET MONITOR ]        " << endl
         << "=========================================" << endl;
    cout << "1. Phoenix" << "   " << "2. Phantom" << endl << "3. Rogue-One" << "    " << "4. Gold" << endl 
         << "5. Red" << "    " << "6. Green" << endl << "7. Blue" << "    " << "8. Grey" << endl << "9. Nova" << "    "
         << "10. Corona" << endl << "11. Hound" << "    " << "12. Vanguard" << endl << "13. Wraith" << "    " << "14. Saber" << endl << "15. Blade" << endl
         << "=========================================" << endl;
    string squad = inputString("Squadron: ");
    Squadron* squadTarget = searchSquadron(hangarDock, squad);
    if (squadTarget != NULL) displayFleet(squadTarget -> headShip, squad);
}

Crew* assignCrewtoShip()
{

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

    }
}



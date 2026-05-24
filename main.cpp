#include <iostream>
#include "planet.hpp"
#include "systemfile.hpp"
#include "crew.hpp"
#include "input.hpp"
#include "spaceship.hpp"
#include "squadron.hpp"
#include "missions.hpp"
using namespace std;

void mainMenu()
{
    bool close = false;
    while (!close)
    {
        system("cls");
        cout << "=========================================" << endl
             << "=== [ REBEL ALLIANCE COMMAND CENTER ] ===" << endl
             << "=========================================" << endl << endl;
        cout << "1. Crew Database" << endl << endl
             << "2. Fleet Menu" << endl << endl
             << "3. Mission Terminal" << endl << endl
             << "4. Galaxy Map" << endl << endl
             << "5. Next Day" << endl << endl
             << "6. Close System" << endl << endl
             << "=========================================" << endl;

        int opt = inputInt("[-] Access Program: ");
        if (opt == 1) 
        {
            crewMenu();
        }
        else if (opt == 2)
        {
            fleetMenu();
        }
        else if (opt == 3)
        {
            missionMenu();
        }
        else if (opt == 4)
        {
            mappingMenu();
        }
        else if (opt == 5)
        {
            dayPass();
        }
        else if (opt == 6)
        {
            saveCrew();
            saveSpaceships();
            saveMissions();
            savePlanetSystem();
            cout << "[!] Closing the system. May the force be with you. . .";
            close = true;
        }        
    }
}

int main()
{   
    loadPlanetSystem();
    initSquadron();
    loadSpaceships();
    loadCrew();
    loadMissions();
    mainMenu();
}
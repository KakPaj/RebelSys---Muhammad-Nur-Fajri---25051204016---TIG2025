#include <iostream>
#include "planet.hpp"
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
        cout << "=========================================" << endl
             << "=== [ REBEL ALLIANCE COMMAND CENTER ] ===" << endl
             << "=========================================" << endl << endl;

        cout << "1. Crew Database" << endl << endl
             << "2. Fleet Monitor" << endl << endl
             << "3. Squadron Monitor" << endl << endl
             << "4. Mission Terminal" << endl << endl
             << "5. Galaxy Map" << endl << endl
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
            squadronMenu();
        }
        else if (opt == 4)
        {
            missionMenu();
        }
        else if (opt == 5)
        {
            mappingMenu();
        }
        else if (opt == 6)
        {
            cout << "[!] Closing the system. May the force be with you. . .";
            close = true;
        }        
    }
}

int main()
{
    mainMenu();
}

// int main()
// {
//     cout << "========== RebelSyS - Rebel Alliance Tactical Operating System =========";
// }
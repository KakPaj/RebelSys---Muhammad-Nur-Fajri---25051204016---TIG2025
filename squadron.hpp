#pragma once
#include <iostream>
#include "spaceship.hpp"
using namespace std;

struct Squadron
{
    string squadName;
    string nameShip;

    Spaceship* headShip = NULL;
    Squadron* next = NULL;
};

const int HANGAR = 15;
Squadron* hangarDock[HANGAR] = {NULL};

int hashSquad(string squadName, int hangar)
{
    int sum = 0;
    for (int i = 0; i < squadName.length();i++) sum += squadName[i];
    return sum % HANGAR;
}

void initSquadron()
{
    string yavinBase[] = {"Phoenix", "Phantom", "Rogue-One", "Gold", "Red", "Green", "Blue", "Grey", "Nova", "Corona", "Hound", "Vanguard", "Wraith", "Saber", "Blade"};
    for (int i = 0;i < HANGAR;i++)
    {
        int idBase = hashSquad(yavinBase[i], HANGAR);
        Squadron* newSquad = new Squadron{yavinBase[i]};
        if (hangarDock[idBase] == NULL)
        {
            hangarDock[idBase] = newSquad;
        }
        else
        {
            Squadron* temp = hangarDock[idBase];
            while (temp -> next != NULL) temp = temp -> next;
            temp -> next = newSquad;
        }
    }
}

Squadron* searchSquadron(Squadron* hangarDock[], string squadName)
{
    int hangarID = hashSquad(squadName, HANGAR);
    Squadron* temp = hangarDock[hangarID];
    while (temp != NULL)
    {
        if (temp -> squadName == squadName) return temp;
        temp = temp -> next;
    }
    return NULL;
}

void addShip()
{

}

void displayHangar()
{

}

#pragma once
#include <iostream>
#include "input.hpp"
using namespace std;

struct Crew
{
    string crewName;
    int rankNum;
    string rankName;

    Crew* left;
    Crew* right;

    Crew* next;
};

Crew* Root = NULL;
string name;
int rankN;
string rankNM;

Crew* insertCrew(Crew* root, Crew* newCrew)
{
    if (root == NULL) return newCrew;
    if (newCrew -> rankNum < root -> rankNum) return root -> left = insertCrew(root -> left, newCrew);
    return root -> right = insertCrew(root -> right, newCrew);
}

Crew* searchCrew(Crew* root, string name, int rank)
{
    if (root == NULL || root -> crewName == name) return root;
    if (root -> rankNum < rank) return root -> left = searchCrew(root -> left, name, rank);
    return root -> right = searchCrew(root -> right, name, rank);
}

void addNewCrew()
{
    while (!close)
    {
        system("cls");
    
        cout << "======= Rebel Alliance Registration Form =======" << endl;
        string name = inputString("Crew Name: ");
        int rank = rankDecode("Rank: ");
        if (searchCrew(Root, name, rankN) != NULL)
        {
            cout << "[-] " << name << "  sudah terdaftar di Database Rebel Alliance!" << endl;
            system("pause");
            return;
        }
        Crew* newCrew = new Crew{name, rankN, rankNM};
        Root = insertCrew(Root, newCrew);
    }
}

int sumCrew(Crew* root)
{
    if (root == NULL) return 0;
    return 1 + sumCrew(root -> left) + sumCrew(root -> right);
}

void holdCrews(Crew* root, Crew* crews[], int& indexCrew)
{
    if (root == NULL) return;
    holdCrews(root -> left, crews, indexCrew);
    crews[indexCrew] = root;
    indexCrew += 1;
    holdCrews(root -> right, crews, indexCrew);
    return;
}

void sortCrew(Crew* crews[], int total, int mode)
{
    for(int i = 0;i < total - 1;i++)
    {
        int hold = i;
        for(int j = i + 1;j < total;j++)
        {
            if (mode == 1)
            {
                if (crews[j] -> crewName < crews[hold] -> crewName)
                {
                    hold = j;
                }
            }
            else if (mode == 2)
            {
                if (crews[j] -> crewName > crews[hold] -> crewName)
                {
                    hold = j;
                }
            }
            else if (mode == 3)
            {
                if (crews[j] -> rankNum > crews[hold] -> rankNum)
                {
                    hold = j;
                }
            }
            else if (mode == 4)
            {
                if (crews[j] -> rankNum < crews[hold] -> rankNum)
                {
                    hold = j;
                }
            }
        }
        if (hold != i)
        {
            Crew* temp = crews[i];
            crews[i] = crews[hold];
            crews[hold] = temp;
        }
    }
    return;
}

void displayAZ()
{
    int total = sumCrew(Root);
    if (total == 0)
    {
        string answer;
        while (answer != "Decline" || answer != "decline" || answer != "D")
        {
            answer = inputString("[-] Crew(s) not found. Initiate add a new crew . . . \n [-] Choice(Accept/Decline): ");
            if (answer == "Accept" || answer == "accept" || answer == "A")
            {
                addNewCrew();
            }
            else
            {
                cout << "[-] Invalid Input! Reprocessing. . .";
            }
        }
    }

    Crew* crews[total];
    int indexCrew = 0;
    holdCrews(Root, crews, indexCrew);
    sortCrew(crews, total, 1);

    cout << "======= Active Personnel Database =======" << endl;
    for(int i = 0; i < total; i++)
    {
        cout << i + 1 << ". " << crews[i] -> crewName << " - " << crews[i] -> rankName << endl;
    }
}

void displayZA()
{
    int total = sumCrew(Root);
    if (total == 0)
    {
        string answer;
        while (answer != "Decline" || answer != "decline" || answer != "D")
        {
            answer = inputString("[-] Crew(s) not found. Initiate add a new crew . . . \n [-] Choice(Accept/Decline): ");
            if (answer == "Accept" || answer == "accept" || answer == "A")
            {
                addNewCrew();
            }
            else
            {
                cout << "[-] Invalid Input! Reprocessing. . .";
            }
        }
    }

    Crew* crews[total];
    int indexCrew = 0;
    holdCrews(Root, crews, indexCrew);
    sortCrew(crews, total, 2);

    cout << "======= Active Personnel Database =======" << endl;
    for(int i = 0; i < total; i++)
    {
        cout << i + 1 << ". " << crews[i] -> crewName << " - " << crews[i] -> rankName << endl;
    }
}

void displayRankAsc()
{
    int total = sumCrew(Root);
    if (total == 0)
    {
        string answer;
        while (answer != "Decline" || answer != "decline" || answer != "D")
        {
            answer = inputString("[-] Crew(s) not found. Initiate add a new crew . . . \n [-] Choice(Accept/Decline): ");
            if (answer == "Accept" || answer == "accept" || answer == "A")
            {
                addNewCrew();
            }
            else
            {
                cout << "[-] Invalid Input! Reprocessing. . .";
            }
        }
    }

    Crew* crews[total];
    int indexCrew = 0;
    holdCrews(Root, crews, indexCrew);
    sortCrew(crews, total, 3);

    cout << "======= Active Personnel Database =======" << endl;
    for(int i = 0; i < total; i++)
    {
        cout << i + 1 << ". " << crews[i] -> crewName << " - " << crews[i] -> rankName << endl;
    }
}

void displayRankDesc()
{
    int total = sumCrew(Root);
    if (total == 0)
    {
        string answer;
        while (answer != "Decline" || answer != "decline" || answer != "D")
        {
            answer = inputString("[-] Crew(s) not found. Initiate add a new crew . . . \n [-] Choice(Accept/Decline): ");
            if (answer == "Accept" || answer == "accept" || answer == "A")
            {
                addNewCrew();
            }
            else
            {
                cout << "[-] Invalid Input! Reprocessing. . .";
            }
        }
    }

    Crew* crews[total];
    int indexCrew = 0;
    holdCrews(Root, crews, indexCrew);
    sortCrew(crews, total, 4);

    cout << "======= Active Personnel Database =======" << endl;
    for(int i = 0; i < total; i++)
    {
        cout << i + 1 << ". " << crews[i] -> crewName << " - " << crews[i] -> rankName << endl;
    }
}

Crew* deleteCrew(Crew* root)
{

}
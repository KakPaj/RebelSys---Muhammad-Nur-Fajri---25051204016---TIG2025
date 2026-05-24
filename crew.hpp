#pragma once
#include <iostream>

using namespace std;

struct Spaceship;

struct Crew
{
    string crewName;
    int rankNum;
    string rankName;
    int status;

    Spaceship* homeShip = NULL;

    Crew* left = NULL;
    Crew* right = NULL;

    Crew* next = NULL;
};

#include "input.hpp"
#include "spaceship.hpp"

Crew* RootCR = NULL;
string name;
int rankN;
string rankNM;

Crew* insertCrew(Crew* root, Crew* newCrew)
{
    if (root == NULL) return newCrew;
    if (newCrew  ->  rankNum < root  ->  rankNum) 
    {
        root  ->  left = insertCrew(root  ->  left, newCrew);
    }
    else if (newCrew  ->  rankNum > root  ->  rankNum) 
    {
        root -> right = insertCrew(root  ->  right, newCrew);
    }
    else 
    {
        if (newCrew  ->  crewName < root  ->  crewName)
        {
            root  ->  left = insertCrew(root  ->  left, newCrew);
        }
        else if (newCrew  ->  crewName > root  ->  crewName)
        {
            root  ->  right = insertCrew(root  ->  right, newCrew);
        }
    }
    return root; 
}

Crew* searchCrew(Crew* root, string name, int rank)
{
    if (root == NULL || root  ->  crewName == name) return root;
    if (root  ->  rankNum > rank) return searchCrew(root  ->  left, name, rank);
    return searchCrew(root  ->  right, name, rank);
}

void addNewCrew()
{
    bool close = false;
    while (!close)
    {
        system("cls");
        cout << "=========================================" << endl
             << "        [ REBEL ALLIANCE LISTING ]       " << endl
             << "=========================================" << endl;

        string name = inputString("Crew Name: ");
        string rank = inputString("Rank: ");
        int rankNum = ranktoNum(rank);

        if (searchCrew(RootCR, name, rankNum) != NULL) 
        {
            cout << "[-] " << name << " has already been listed in the Rebel Alliance database!" << endl;
            system("pause");
            return;
        }


        Crew* newCrew = new Crew();
        newCrew -> crewName = name;
        newCrew -> rankName = rank;
        newCrew -> rankNum = rankNum;
        newCrew -> status = 0;
        newCrew -> homeShip = NULL;
        newCrew -> left = NULL;
        newCrew -> right = NULL;

        RootCR = insertCrew(RootCR, newCrew);

        cout << "[+] " << name << " successfully recruited!" << endl;
        cout << "=========================================" << endl;
        system("pause");
        close = true;
    }
}

int sumCrew(Crew* root)
{
    if (root == NULL) return 0;
    return 1 + sumCrew(root  ->  left) + sumCrew(root  ->  right);
}

void holdCrews(Crew* root, Crew* crews[], int& indexCrew)
{
    if (root == NULL) return;
    holdCrews(root  ->  left, crews, indexCrew);
    crews[indexCrew] = root;
    indexCrew += 1;
    holdCrews(root  ->  right, crews, indexCrew);
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
                if (crews[j]  ->  crewName < crews[hold]  ->  crewName)
                {
                    hold = j;
                }
            }
            else if (mode == 2)
            {
                if (crews[j]  ->  crewName > crews[hold]  ->  crewName)
                {
                    hold = j;
                }
            }
            else if (mode == 3)
            {
                if (crews[j]  ->  rankNum > crews[hold]  ->  rankNum)
                {
                    hold = j;
                }
            }
            else if (mode == 4)
            {
                if (crews[j]  ->  rankNum < crews[hold]  ->  rankNum)
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
    int total = sumCrew(RootCR);
    if (total == 0)
    {
        string answer;
        while (answer != "Decline" && answer != "decline" && answer != "D")
        {
            answer = inputString("[-] Crew(s) not found. Initiate add a new crew . . . \n[-] Choice(Accept/Decline): ");
            if (answer == "Accept" || answer == "accept" || answer == "A")
            {
                addNewCrew();
                answer = "D";
                total = sumCrew(RootCR);
                system("cls");
            }
            else
            {
                cout << "[-] Invalid Input! Reprocessing. . .";
            }
        }
    }

    Crew* crews[total];
    int indexCrew = 0;
    holdCrews(RootCR, crews, indexCrew);
    sortCrew(crews, total, 1);

    cout << "=========================================" << endl
         << "           [ ALL ACTIVE CREW ]           " << endl
         << "================== A-Z ==================" << endl;

    for(int i = 0; i < total; i++)
    {
        if (crews[i]  ->  status != 3) cout << i + 1 << ". " << crews[i]  ->  crewName << " - " << crews[i]  ->  rankName << endl;
    }
    cout << "=========================================" << endl;
}

void displayZA()
{
    int total = sumCrew(RootCR);
    if (total == 0)
    {
        string answer;
        while (answer != "Decline" && answer != "decline" && answer != "D")
        {
            answer = inputString("[-] Crew(s) not found. Initiate add a new crew . . . \n[-] Choice(Accept/Decline): ");
            if (answer == "Accept" || answer == "accept" || answer == "A")
            {
                addNewCrew();
                answer = "D";
                total = sumCrew(RootCR);
                system("cls");
            }
            else
            {
                cout << "[-] Invalid Input! Reprocessing. . .";
            }
        }
    }

    Crew* crews[total];
    int indexCrew = 0;
    holdCrews(RootCR, crews, indexCrew);
    sortCrew(crews, total, 2);

    cout << "=========================================" << endl
         << "           [ ALL ACTIVE CREW ]           " << endl
         << "================== Z-A ==================" << endl;

    for(int i = 0; i < total; i++)
    {
        if (crews[i]  ->  status != 3) cout << i + 1 << ". " << crews[i]  ->  crewName << " - " << crews[i]  ->  rankName << endl;
    }
    cout << "=========================================" << endl;
}

void displayRankAsc()
{
    int total = sumCrew(RootCR);
    if (total == 0)
    {
        string answer;
        while (answer != "Decline" && answer != "decline" && answer != "D")
        {
            answer = inputString("[-] Crew(s) not found. Initiate add a new crew . . . \n[-] Choice(Accept/Decline): ");
            if (answer == "Accept" || answer == "accept" || answer == "A")
            {
                addNewCrew();
                answer = "D";
                total = sumCrew(RootCR);
                system("cls");
            }
            else
            {
                cout << "[-] Invalid Input! Reprocessing. . .";
            }
        }
    }

    Crew* crews[total];
    int indexCrew = 0;
    holdCrews(RootCR, crews, indexCrew);
    sortCrew(crews, total, 3);

    cout << "=========================================" << endl
         << "           [ ALL ACTIVE CREW ]           " << endl
         << "=============== RANK ASC ================" << endl;

    for(int i = 0; i < total; i++)
    {
        if (crews[i]  ->  status != 3) cout << i + 1 << ". " << crews[i]  ->  crewName << " - " << crews[i]  ->  rankName << endl;
    }
    cout << "=========================================" << endl;
}

void displayRankDesc()
{
    int total = sumCrew(RootCR);
    if (total == 0)
    {
        string answer;
        while (answer != "Decline" && answer != "decline" && answer != "D")
        {
            answer = inputString("[-] Crew(s) not found. Initiate add a new crew . . . \n[-] Choice(Accept/Decline): ");
            if (answer == "Accept" || answer == "accept" || answer == "A")
            {
                addNewCrew();
                answer = "D";
                total = sumCrew(RootCR);
                system("cls");
            }
            else
            {
                cout << "[-] Invalid Input! Reprocessing. . .";
            }
        }
    }

    Crew* crews[total];
    int indexCrew = 0;
    holdCrews(RootCR, crews, indexCrew);
    sortCrew(crews, total, 4);

    cout << "=========================================" << endl
         << "           [ ALL ACTIVE CREW ]           " << endl
         << "=============== RANK DESC ===============" << endl;

    for(int i = 0; i < total; i++)
    {
        if (crews[i]  ->  status != 3) cout << i + 1 << ". " << crews[i]  ->  crewName << " - " << crews[i]  ->  rankName << endl;
    }
    cout << "=========================================" << endl;
}

void displayActive()
{
    system("cls");
    displayAZ();
    string choice;
    while(choice != "X" && choice != "x")
    {
        choice = inputString("[A] A-Z [Z] Z-A [+] Rank Asc [-] Rank Desc [X] Exit\n[-] Filter: ");
        if(choice == "A" || choice == "a")
        {
            system("cls");
            displayAZ();
        }
        else if(choice == "Z" || choice == "z")
        {
            system("cls");
            displayZA();
        }
        else if(choice == "+")
        {
            system("cls");
            displayRankAsc();
        }
        else if(choice == "-")
        {
            system("cls");
            displayRankDesc();
        }
    }
}

void displaySearchCrew(Crew* target)
{
    if (target == NULL)
    {
        cout << "\n[-] Crew member not found in the database." << endl;
    }
    else
    {
        cout << endl << "=========================================" << endl
                     << "             [ CREW DETAIL ]             " << endl
                     << "=========================================" << endl
                     << " Name   : " << target -> crewName << endl
                     << " Rank   : " << target -> rankName << endl;
        
        cout << " Status : ";
        if (target->status == 0) cout << "Standby (Base)" << endl;
        else if (target->status == 1) cout << "Assigned (On Ship)" << endl;
        else if (target->status == 2) cout << "Deployed (On Mission)" << endl;
        else if (target->status == 3) cout << "K.I.A (Killed In Action)" << endl;
        
        cout << "=========================================\n" << endl;
    }
}

void initSearchCrew()
{
    system("cls");
    cout << "=========================================" << endl
         << "        [ SEARCH CREW DATABASE ]         " << endl
         << "=========================================" << endl;
         
    string name = inputString("Name: ");
    string rank = inputString("Rank: ");
    int rankNM = ranktoNum(rank);
    
    Crew* foundCrew = searchCrew(RootCR, name, rankNM);
    
    displaySearchCrew(foundCrew);
    
    system("pause");
}

void crewMenu()
{
    bool back = false;
    while (!back)
    {
        system("cls");
        cout << "=========================================" << endl
            << "              [ CREW MENU ]             " << endl
            << "=========================================" << endl
            << "1. New Crew" << endl << endl
            << "2. Search Crew" << endl << endl
            << "3. All Active Crew" << endl << endl
            << "4. Back to Command Center" << endl << endl
            << "=========================================" << endl;
        int opt = inputInt("[-] Choice: ");
        if (opt == 1) 
        {
            addNewCrew();
        }
        else if (opt == 2)
        {
            initSearchCrew();
        }
        else if (opt == 3)
        {
            displayActive();
        }
        else if (opt = 4)
        {
            back = true;
        }
    }

}
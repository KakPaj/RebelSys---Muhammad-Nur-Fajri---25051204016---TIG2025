#pragma once
#include <iostream>
#include "crew.hpp"
using namespace std;

bool close = false;

string inputString(string prompt) {
    string temp;
    cout << prompt;
    getline(cin, temp);
    return temp;
}

int inputInt(string prompt) {
    string temp = inputString(prompt);
    if (temp.empty()) return 0;
    try { return stoi(temp); } catch (...) { return 0; }
}

int rankDecode(string prompt)
{
    string holdPrompt = prompt;
    rankNM = inputString(prompt);
    if (rankNM == "Lieutenant") return 1;
    else if (rankNM == "Captain") return 2;
    else if (rankNM == "Major") return 3;
    else if (rankNM == "Commander") return 4;
    else if (rankNM == "Colonel") return 5;
    else if (rankNM == "General") return 6;
    else 
    {
        cout << "[-] Invalid Rank! Reprocessing. . ." << endl;
        system("pause");
        rankDecode(holdPrompt);
    }
}

float inputFloat(string prompt) {
    string temp = inputString(prompt);
    if (temp.empty()) return 0.0;
    try { return stof(temp); } catch (...) { return 0.0; }
}

int getString(string input, string output[], char divider = ',')
{
    int count = 0;
    string temp;
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == divider)
        {
            int start = 0;
            while (start < temp.length() && temp[start] == ' ') start++;
            if (start < temp.length()) output[count++] = temp.substr(start);
            temp = "";
        }
        else
        {
            temp += input[i];
        }
    }
    if (temp != "")
    {
        int start = 0;
        while (start < temp.length() && temp[start] == ' ') start++;
        if (start < temp.length()) output[count++] = temp.substr(start);
    }
    return count;
}

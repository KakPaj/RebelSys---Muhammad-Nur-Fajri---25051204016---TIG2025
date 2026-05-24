#pragma once
#include <iostream>
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

int ranktoNum(string rank)
{
    if (rank == "Lieutenant") return 1;
    else if (rank == "Captain") return 2;
    else if (rank == "Major") return 3;
    else if (rank == "Commander") return 4;
    else if (rank == "Colonel") return 5;
    else if (rank == "General") return 6;
    else return 0;
}

float inputFloat(string prompt) {
    string temp = inputString(prompt);
    if (temp.empty()) return 0.0;
    try { return stof(temp); } catch (...) { return 0.0; }
}


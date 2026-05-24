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

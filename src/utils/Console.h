#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
using namespace std;

namespace Console
{

    inline void clearScreen()
    {

        cout << "\033[2J\033[1;1H";
    }

    inline void pause()
    {
        cout << "\nPress Enter to continue...";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    inline void sleepMs(int milliseconds)
    {
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }

    inline void clearInputBuffer()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

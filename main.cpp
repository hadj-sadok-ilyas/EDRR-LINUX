#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include "edr.functions.h"
using namespace std;

int main()
{
    if (DetectOS()!="linux") {
        cout << "Unsupported OS detected, this function is for linux only" << endl;
    }
    cout << "Choose your function:\n"
            "   1-FIM\n"
            "   2-FUTURE functions... to be added later\n" << endl;
    string choice;
    string filename;
    cin >> choice;
    if (choice == "1") {
        WindowsFIM();
    }
    return 0;
}
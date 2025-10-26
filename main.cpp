#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string names[], string colors[]);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    bool ag = true;

    list<Goat> trip;

    int choice;
    while (ag)
    {
        choice = main_menu();
        switch (choice)
        {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                ag = false;
                break;
            default:
                break;
        }

    }







    return 0;
}


int select_goat(list<Goat> trip)
{
    int choice;
    display_trip(trip);

    cout << "\nEnter the goat index that you want to remove" << endl;
    cin >> choice;

    if (cin.fail())
    {
        cin.clear(); //clear flags
        cin.ignore(1000, '\n');
        return 0;
    }

    return choice;

    return 0;
}

void delete_goat(list<Goat> &trip)
{
    if (trip.empty())
    {
        cout << "No goats to delete" << endl;
        return;
    }

    int choice = select_goat(trip);
    if (choice < 1 || choice > trip.size())
    {
        cout << "\nInvalid Choice." << endl;
        return;
    }

    int index = 1; // start counting from 1
    for (list<Goat>::iterator it = trip.begin(); it != trip.end(); it++, index++)
    {
        if (index == choice) {
            cout << "Removing: ";
            it->display(); // show which one is being removed

            trip.erase(it);
            return;
        }
    }

}

void add_goat(list<Goat> &trip, string names[], string colors[])
{
    // generate random attributes
    int nameID = rand() % SZ_NAMES;
    int colorID = rand() % SZ_COLORS;
    int age = rand() % MAX_AGE + 1;

    Goat goat(names[nameID], age, colors[colorID]);
    trip.push_back(goat);

    cout << "Added ";
    goat.display();
    cout << " to the trip" << endl;
}

void display_trip(list<Goat> trip)
{
    if (trip.empty())
    {
        cout << "No goats in the trip" << endl;
        return; // exit method   
    }

    cout << "Current Goat Trip:" << endl;
    int index = 1; // loop through the list and output
    for (list<Goat>::iterator it = trip.begin(); it != trip.end(); it++)
    {
        cout << "[" << setw(2) << index << "] ";
        // use helper function
        it->display();

        cout << endl;
        // forgot to this last time
        index++;
    }
}

int main_menu()
{
    int choice;
    cout << "\n****GOAT MANAGER 3001****" << endl
        << "[1] Add a goat" << endl
        << "[2] Delete a goat" << endl
        << "[3] List Goats" << endl
        << "[4] Quit" << endl
        << "Choice --> ";
    cin >> choice;

    if (cin.fail())
    {
        cin.clear(); //clear flags
        cin.ignore(1000, '\n');
        return 0;
    }

    return choice;
}


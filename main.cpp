// Copyright 2023 Robert Zank

#include <iostream>
#include <fstream>
#include <string>
#include "./CrewApp.h"
#include <set>

using std::string;
using std::cout;
using std::cin;
using std::endl;

/*
Coding trail: 

1. In this submission I impliment the program's recieveing of the command line arguements.
Along with this, the program supposidly checks if the command like arguements entered are correct.
If they are not correct the user will be notified with an error message what went wrong. 

2. In this submission I impliment the Crew.h file into Crew.cpp.

3. In this submission I wrote the skeleton implimentation for CrewApp.cpp.
Also, I wrote the implimentations for Flight.h in Flight.cpp

4. Fixed the ifstream initualizations

5. The loadFiles method was created to shorten up the main method and readability.
A CrewApp is created with the flie names.

6. LoadFlights was implimented to assist with populating the flights vector in the mainCrewApp.
    To help with this process I impimened a AddFlight method in CrewApp

7. LoadCrew was implimented to assist with populating the crew vector in the mainCrewApp.
    To help with this process I impimened a AddCrew method in CrewApp

8. Wrote code to print the menu and promp them with it until they enter -1 and the press enter to continue code

9. Implimented the code to print the crew when the user enters 1
Implimented the code in the case the user enters -1
Edited the LoadFlight method to also populate the uniqueFLocations set
    To assist with this I added an AddLocation method to CrewApp
Implimented code in the case that the user enters 2
Implimented the code for PrintUniqueLocations() in the CrewApp.cpp

10. FindPairIndex() was added to find the index in the 11 scheduled flights of thye entered flight
PrintAttendingCrew() was added, uses that index to look at the crews schedule for that flight,
and prints out the crew that will be on that flight. 
Used bothof thse to carry out the approprate actions if the user enters 3

11. Added the sum of Crew members attending the flight in PrintAttendingCrew().
Changed that the user doesn't have to type case-sensitivly when searching for a flight. 
Implimentations in the case that the user enters 4:
    Created the GetSchedule() method to return the schedule of a specific person
    Prompts the user until they enter a valid name 
    Note: the entry is not case-sensivitive
    Prints out the flights that the crew member will be on

12. Trying to get Makefile to work

13. Changing general formatting with the output
Trying to get the zybook to work...again

14. Comments were added

*/


/*
The purpose of this program is to keet track of flights and the crews for those flights.
This can be used to view data that the program will pull from a file, parse and process all of the data. 
After that the user can do 1 of four actions that use that data to get the requested information. 
*/

/*
This method will take a string and return it in all uppercase
*/
string toUpperCase(string str) {
    string upperStr;
    for (char c : str) {
        upperStr += std::toupper(c);
    }
    return upperStr;
}

/*
This method was implimented to populate the flights vector and the uniqueFLocations vector in the crewApp
*/
void loadFlights(std::ifstream& inFlights, CrewApp& mainCrewApp) {
    string tempFrom, tempTo;

    inFlights >> tempFrom >> tempTo;
    while (!inFlights.fail()) {
        mainCrewApp.AddLocation(tempFrom);
        mainCrewApp.AddLocation(tempTo);

        Flight tempFlight(tempFrom, tempTo);
        mainCrewApp.AddFlight(tempFlight);

        inFlights >> tempFrom >> tempTo;
    }
}

/*
This method was implimented to populate the crews vector in the crewApp
*/
void loadCrew(std::ifstream& inCrew, CrewApp& mainCrewApp) {
    string tempName, tempSchedule;
    inCrew >> tempName >> tempSchedule;
    while (!inCrew.fail()) {
        Crew tempCrew(tempName, tempSchedule);
        mainCrewApp.AddCrew(tempCrew);
        inCrew >> tempName >> tempSchedule;
    }
}

/*
This method was written to assist with the opening process of files and check to see if the files provided are valid
*/
void loadFiles(const string inCrewFile, const string inFlightsFile, std::ifstream& inCrew, std::ifstream& inFlights) {
    // open the file with the crew inofrmation
    inCrew.open(inCrewFile);
    // check to see if the opening of the file worked
    if (!inCrew.is_open()) {
        // if the program could not open the file correctly this message is displayed 
        cout << "The filename given for crews was not found!!!" << endl;
    }

    // Open the file with the flights
    inFlights.open(inFlightsFile);
    // check to see if the opening of the file worked
    if (!inFlights.is_open()) {
        // if the program could not open the file correctly this message is displayed 
        cout << "The filename given for flights was not found!!!" << endl;
    }

    // If either of the files could not be opened, this message is displayed and the program ends
    if (!inCrew.is_open() || !inFlights.is_open()) {
        cout << "Program ends with an error." << endl;
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    // Input File stream
    std::ifstream inCrew;
    std::ifstream inFlights;

    // FileName strings
    string inCrewFile, inFlightsFile;

// Verify Command Line Arguments
    if (argc != 3) {
        cout << "Error!!! Incorrect program arguments\nFormat : applicationName [filenameForCrew] [filenameForFlight]" << endl;
        return 0;
    } else {
        inCrewFile = argv[1];
        inFlightsFile = argv[2];
        loadFiles(inCrewFile, inFlightsFile, inCrew, inFlights);
    }

// Initialize a CrewApp object using the provided filenames.
    CrewApp mainCrewApp(inCrewFile, inFlightsFile);
    // load the flights into mainCrewApp
    loadFlights(inFlights, mainCrewApp);
    //load crew into mainCrewApp
    loadCrew(inCrew, mainCrewApp);
// Utilize the relevant methods of the CrewApp object to display the menu.
    string option = "-2";
// Prompt the user to select a menu option and execute it until -1 is entered.
    while (option != "-1") {
        // Print the menu
        mainCrewApp.PrintMenu();
        cout << "Enter your choice >> ";
        cin >> option;
        //Excecute the menu with the option
        mainCrewApp.ExecuteMenu(option, mainCrewApp);
        // wait to continue until the user presses enter
        cout << "\nto continue, press enter... \n";
            cin.ignore();
            cin.ignore();
    }

}

// Copyright 2023 Robert Zank

#include <iostream>
#include <fstream>
#include <string>
#include "./CrewApp.h"
// Implement CrewApp function members here

CrewApp::CrewApp() {
    crewfileName = "";
    flightfileName = "";
}

CrewApp::CrewApp(std::string crewfileName, std::string flightfileName) {
    this->crewfileName = crewfileName;
    this->flightfileName = flightfileName;
}

std::string CrewApp::toUpperCase(std::string str) {
    std::string upperStr;
    for (char c : str) {
        upperStr += std::toupper(c);
    }
    return upperStr;
}

void CrewApp::AddFlight(Flight tempFlight) {
    flights.push_back(tempFlight);
}

void CrewApp::AddCrew(Crew tempCrew) {
    crews.push_back(tempCrew);
}

void CrewApp::AddLocation(std::string tempLocation) {
    uniqueFLocations.insert(tempLocation);
}

void CrewApp::PrintMenu() {
    // Implement code to print the menu
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Airline Crew Scheduling Application" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " 1 List crew names" << std::endl;
    std::cout << " 2 List all flight locations" << std::endl;
    std::cout << " 3 List crews for the flight" << std::endl;
    std::cout << " 4 List flights for the crew" << std::endl;
    std::cout << "-1 Exit" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

void CrewApp::PrintCrews() {
    // Implement code to print crews
    std::cout << "---- Crew List ----" << std::endl;
    for (int i = 0; i < crews.size(); i++) {
        std::cout << crews.at(i).getName() << std::endl;
    }
}

void CrewApp::PrintUniqueLocations() {
    // Implement code to print unique locations
    std::cout << "--- Flight Locations ---" << std::endl;
    for (std::string str : uniqueFLocations) {
        std::cout << str << std::endl;
    }
}

void CrewApp::ExecuteMenu(std::string& option, CrewApp& mainCrewApp) {
// Implement code to execute menu based on the option
    if (option == "1") {
        mainCrewApp.PrintCrews();
    } else if (option == "2") {
        mainCrewApp.PrintUniqueLocations();
    } else if (option == "3") {
        mainCrewApp.PrintUniqueLocations();
        // boolean to see if the program finds the flight that the user is looking for
        bool check = false;
        // loop until the user enters a valid flight
        while (!check) {
            // promp the user for the from and to
            std::cout << "\nFROM >> ";
            std::string tempFrom, tempTo;
            std::cin >> tempFrom;
            std::cout << "TO >> ";
            std::cin >> tempTo;

            // convert the input to uppercase
            std::string upperTempFrom, upperTempTo;
            upperTempFrom = toUpperCase(tempFrom);
            upperTempTo = toUpperCase(tempTo);

            // Get the index of the flight in the flight list
            int index = mainCrewApp.FindPairIndex(upperTempFrom, upperTempTo);
            if (index != -1) {
                check = true;
                // If  flight is found the attending crew is printed
                mainCrewApp.PrintAttendingCrew(index);
                std::cout << upperTempFrom << "-" << upperTempTo << std::endl;
            } else {
                std::cout << "No flight was found!! Please try again..." << std::endl;
            }
        }
    } else if (option == "4") {
        std::string name, schedule;
        // get the name form the user
        std::cout << "Enter the crew name >> ";
        // boolean to see if the crew member is found in the Crew list
        bool check = false;
        //keep prompting unitl a valid name is entered
        while (!check) {
            // get the name
            std::cin >> name;
            //return the schedule of the crew member (returns -1 if there is no member, and -2 if the member has no flighs)
            schedule = mainCrewApp.GetSchedule(toUpperCase(name));
            // If name is found and they have flights
            if (schedule != "-1" && schedule != "-2") {
                check = true;
            // if the neme is not found
            } else if (schedule == "-1") {
                std::cout << "No record for " << toUpperCase(name) << ". Please try again..." << std::endl;
            // if the name was found but no flights are assigned to them
            } else {
                check = true;
                std::cout << "No flight was assigned to " << toUpperCase(name) << std::endl;
            }
        }
    // termnate program if the user enters -1
    } else if (option == "-1") {
        std::cout << "Bye!" << std::endl;
        exit(0);
    // print statement if the user enters an invalid choice
    } else {
        std::cout << "The wrong choice!!!" << std::endl;
    }
}

void CrewApp::PrintAttendingCrew(int index) {
    int count = 0;
    std::cout << "---- Crew List ----" << std::endl;
    for (int i = 0; i < crews.size(); i ++) {
        std::string schedule = crews.at(i).getSchedule();
        if (schedule.substr(index, 1) == "1") {
            count++;
            std::cout << crews.at(i).getName() << std::endl;
        }
    }
    std::cout << count << " crew(s) work(s) on the flight ";
}

int CrewApp::FindPairIndex(std::string tempFrom, std::string tempTo) {
    for (int i = 0; i < flights.size(); i++) {
        if (tempFrom == flights.at(i).getFrom() && tempTo == flights.at(i).getTo()) {
            return i;
        }
    }
    return -1;
}

std::string CrewApp::GetSchedule(std::string name) {
    std::cout << "---- Assigned Flights ----" << std::endl;
    // loop to compare the perameter with each crew member
    for (int i = 0; i < crews.size(); i++) {
        std::string nameUpper = "";
        // change the being compared to uppercase
        for (char e : crews.at(i).getName()) {
            nameUpper += std::toupper(e);
        }

        // boolean to check to see if the schedule is feaseable
        bool trigger = true;
        // boolean to see if the member is on any flights
        bool onAnyFlights = false;
        // if the perameter and the name being compared equal
        if (nameUpper == name) {
            std::string schedule = crews.at(i).getSchedule();
            std::string prevDest = "-1";
            int count = 0;
            // loop through the schedule to see what flights the member is on
            for (char e : schedule) {
                if (e == '1') {
                    onAnyFlights = true;
                    // print out the flight that the member is on when 1 is caught
                    std::cout << flights.at(count).getFrom() << " - " << flights.at(count).getTo() << std::endl;
                    // if the member is on a not feaseable schedule the trigger is changed to false
                    if (prevDest != "-1" && prevDest != flights.at(count).getFrom()) {
                        trigger = false;
                    }
                    // set the previous destination so we cansee if the schedule is feaseable
                    prevDest = flights.at(count).getTo();
                } else {
                    prevDest = "-1";
                }
                // count for index 
                count++;
            }
            if (trigger && onAnyFlights) {
                std::cout << "The flight sequence is feasible" << std:: endl;
            } else if (onAnyFlights) {
                std::cout << "The flight sequence is NOT feasible" << std:: endl;
            }
            if (onAnyFlights) {
                return crews.at(i).getSchedule();
            } else {
                return "-2";
            }
        }
    }
    return "-1";
}

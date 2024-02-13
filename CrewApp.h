// Copyright 2023 Robert Zank

#ifndef CREWAPP_H
#define CREWAPP_H
#include <vector>
#include <string>
#include <set>
#include "Crew.h"
#include "Flight.h"

class CrewApp {
    private:
        std::vector<Flight> flights;
        std::vector<Crew> crews;
        std::set<std::string> uniqueFLocations;
        std::string crewfileName;
        std::string flightfileName;
    public:
        CrewApp();
        CrewApp(std::string crewfileName, std::string flightfileName);
        std::string toUpperCase(std::string str);
        void AddFlight(Flight tempFlight);
        void AddCrew(Crew tempCrew);
        void AddLocation(std::string tempLocation);
        void PrintMenu();
        void PrintCrews();
        void PrintUniqueLocations();
        void ExecuteMenu(std::string& option, CrewApp& mainCrewApp);
        void PrintAttendingCrew(int index);
        int FindPairIndex(std::string tempFrom, std::string tempTo);
        std::string GetSchedule(std::string);
};
#endif


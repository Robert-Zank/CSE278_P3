// Copyright 2023 Robert Zank

#ifndef CREW_H
#define CREW_H
#include<string>
class Crew {
    private:
        std::string name;
        std::string schedule;
    public:
        Crew();
        Crew(std::string name, std::string schedule);
        void setName(std::string name);
        void setSchedule(std::string schedule);
        std::string getName();
        std::string getSchedule();
           
};
#endif
// Copyright 2023 Robert Zank

#ifndef FLIGHT_H
#define FLIGHT_H
#include<string>

class Flight {
    private:
        std::string from;
        std::string to;
    public:
        Flight();
        Flight(std::string from, std::string to);
        void setFlight(std::string from, std::string to);
        std::string getFrom();
        std::string getTo();
};
#endif

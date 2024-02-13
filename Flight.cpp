// Copyright 2023 Robert Zank

#include "Flight.h"

// Implement the Flight member functions here

Flight::Flight() {
    from = "";
    to = "";
}

Flight::Flight(std::string from, std::string to) {
    this->from = from;
    this->to = to;
}

void Flight::setFlight(std::string from, std::string to) {
    this->from = from;
    this->to = to;
}

std::string Flight::getFrom() {
    return from;
}

std::string Flight::getTo() {
    return to;
}


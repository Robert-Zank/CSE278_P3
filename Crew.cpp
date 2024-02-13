// Copyright 2023 Robert Zank

#include "Crew.h"

Crew::Crew() {
    name = "";
    schedule = "";
}

Crew::Crew(std::string name, std::string schedule) {
    this->name = name;
    this->schedule = schedule;
}

void Crew::setName(std::string name) {
    this->name = name;
}

void Crew::setSchedule(std::string schedule) {
    this->schedule = schedule;
}

std::string Crew::getName() {
    return name;
}

std::string Crew::getSchedule() {
    return schedule;
}


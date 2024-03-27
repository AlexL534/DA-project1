#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Reservoir.h"
#include "Station.h"
#include "Pipe.h"
#include "City.h"
#include "parse.h"

std::vector<Reservoir> parseReservoirs() {
    std::vector<Reservoir> reservoirs;
    std::ifstream file("../Dataset/Reservoir.csv");

    if (!file.is_open()) {
        std::cout << "Error: Unable to open Reservoir.csv\n";
        return reservoirs;
    }

    std::string line;
    std::string name,municipality,code;
    int id, maxDelivery;
    getline(file,line);
    while(getline(file,line)) {
        std::istringstream iss(line);
        getline(iss,name,',');
        getline(iss,municipality,',');
        iss >> id;
        iss.ignore();
        getline(iss,code,',');
        iss >> maxDelivery;

        Reservoir reservoir(name, municipality, id, code, maxDelivery);
        reservoirs.emplace_back(reservoir);

    }
    return reservoirs;
}

std::vector<Station> parseStations() {
    std::vector<Station> stations;
    std::ifstream file("../Dataset/Stations.csv");

    if (!file.is_open()) {
        std::cout << "Error: Unable to open Station.csv\n";
        return stations;
    }

    std::string line;
    int id;
    std::string code;
    getline(file,line);
    while(getline(file,line)) {
        std::istringstream iss(line);
        iss >> id;
        iss.ignore();
        getline(iss,code,',');

        Station station(id, code);
        stations.emplace_back(station);

    }
    return stations;
}

std::vector<Pipe> parsePipes() {
    std::vector<Pipe> pipes;
    std::ifstream file("../Dataset/Pipes.csv");

    if (!file.is_open()) {
        std::cout << "Error: Unable to open Pipes.csv\n";
        return pipes;
    }

    std::string line;
    std::string pointA,pointB;
    int capacity,direction;
    getline(file,line);
    while(getline(file,line)) {
        std::istringstream iss(line);
        getline(iss,pointA,',');
        getline(iss,pointB,',');
        iss >> capacity;
        iss.ignore();
        iss >> direction;

        Pipe pipe(pointA,pointB,capacity,direction);
        pipes.emplace_back(pipe);

    }
    return pipes;
}

std::vector<City> parseCities() {
    std::vector<City> cities;
    std::ifstream file("../Dataset/Cities.csv");

    if (!file.is_open()) {
        std::cout << "Error: Unable to open Cities.csv\n";
        return cities;
    }

    std::string line;
    std::string name,code;
    int id, population;
    float demand;
    getline(file,line);
    while(getline(file,line)) {
        std::istringstream iss(line);
        getline(iss,name,',');
        iss >> id;
        iss.ignore();
        getline(iss,code,',');
        iss >> demand;
        iss.ignore();
        iss >> population;

        City city(name,id,code,demand,population);
        cities.emplace_back(city);

    }
    return cities;
}

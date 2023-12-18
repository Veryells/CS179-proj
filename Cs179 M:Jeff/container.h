#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#ifndef CONTAINER_H
#define CONTAINER_H

enum class Condition { N, F, U };

class Container {
private:
    unsigned int locationX, locationY;
    int weight;
    std::string description;

public:
    Container(unsigned int locationX, unsigned int locationY, int weight, const std::string& description)
        : locationX(locationX), locationY(locationY), weight(weight), description(description) {}
    unsigned int getlocationX() const;
    unsigned int getlocationY() const;
    int getWeight() const;
    std::string getDescription() const;
};
#endif

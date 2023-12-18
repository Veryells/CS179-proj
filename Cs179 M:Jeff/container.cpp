#include "container.h"

unsigned int Container::getlocationX() const {
    return locationX;
}


unsigned int Container::getlocationY() const {
    return locationY;
}

int Container::getWeight() const {
    return weight;
}

std::string Container::getDescription() const {
    return description;
}
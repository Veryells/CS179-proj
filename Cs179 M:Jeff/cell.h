#ifndef CELL_H
#define CELL_H
#include "container.h"

class Cell {
private:
    char state;
    Container* container;

public:
    Cell() : state(static_cast<char>(Condition::U)), container(nullptr) {}
    Cell(char state) : state(state), container(nullptr) {}
    Cell(char state, Container* container) : state(state), container(container) {}

    void setContainer(Container* newContainer);
    void clearContainer();
    Container* getContainer() const;
    char getState() const;
    void setState(char newState);
};

void Cell::setContainer(Container* newContainer) {
    container = newContainer;
}

void Cell::clearContainer() {
    if (container != nullptr) {
        container = nullptr;
    }
}

Container* Cell::getContainer() const {
    return container;
}

char Cell::getState() const {
    return state;
}

void Cell::setState(char newState) {
    state = newState;
}
#endif
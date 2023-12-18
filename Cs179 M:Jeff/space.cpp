#include "space.h"

void Space::setN(const int row, const int col)
{ 
    cells[row][col].setState(static_cast<char>(Condition::N));
}

void Space::setF(const int row, const int col, Container *container)
{
    cells[row][col].setState(static_cast<char>(Condition::F));
    cells[row][col].setContainer(container);
}

void Space::removeContainer(const int row, const int col)
{
    if (cells[row][col].getState() != static_cast<char>(Condition::F))
        throw 9;
    cells[row][col].setState(static_cast<char>(Condition::U));
}

void Space::processContainer(const int row, const int col, Container* container) {
    if (container->getDescription() == "NAN") {
        setN(row, col);
    } else if (container->getDescription() == "UNUSED") {
        removeContainer(row, col);
    } else  {
        setF(row, col, container);
    } 
}

Cell Space::getCell(const int row, const int col) const
    {
        return cells[row][col];
    }

char Space::getCellState(const int row, const int col) const
    {
        return cells[row][col].getState();
    }


#ifndef SPACE_H
#define SPACE_H
#include "container.h"
#include "cell.h"

class Space {
    private:
    int rows;
    int cols;
    Cell** cells;

    public:
    Space(int row, int cols);
    void setN(const int row, const int cols);
    void setF(const int row, const int cols, Container* container);
    void addContainer(const int row, const int cols, Container* container);
    void removeContainer(const int row, const int cols);
    void processContainer(const int row, const int cols, Container* container);

    Cell getCell(const int row, const int cols) const;
    char getCellState(const int row, const int cols) const;
    


    ~Space();
    
};
#endif

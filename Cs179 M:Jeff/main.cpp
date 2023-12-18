#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <limits>


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
//_________________________________________________________________________________________________________
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
//_________________________________________________________________________________________________________
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
//_________________________________________________________________________________________________________

class Space {
    private:
    int rows;
    int cols;
    Cell** cells;

    public:
    Space(int row, int cols);
    void setN(const int row, const int cols);
    void setF(const int row, const int cols, Container* container);
    void removeContainer(const int row, const int cols);
    void processContainer(const int row, const int cols, Container* container);

    Cell getCell(const int row, const int cols) const;
    char getCellState(const int row, const int cols) const;
    
    ~Space();
    
};

//_________________________________________________________________________________________________________

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

//_________________________________________________________________________________________________________

void displayValidContainers(const std::vector<Container>& containers) {
    for (const auto& container : containers) {
        if (container.getDescription() != "NAN" && container.getDescription() != "UNUSED") {
            std::cout << "Location: [" << container.getlocationX() << "," << container.getlocationY() << "], Weight: " << container.getWeight() << ", Description: " << container.getDescription() << std::endl;
        }
    }
}

void chooseContainers(std::vector<Container>& containers, std::vector<Container>& selectedContainers) {
    std::cout << "Choose containers:" << std::endl;

    for (const auto& container : containers) {       
        if (container.getDescription() != "NAN" && container.getDescription() != "UNUSED") {
        std::cout << "Location: [" << container.getlocationX() << "," << container.getlocationY() << "], Weight: " << container.getWeight() << ", Description: " << container.getDescription() << std::endl;
       
        char choice;
        do {
            std::cout << "Checkbox: (y/n): ";
            std::cin >> choice;
        } while (choice != 'y' && choice != 'n');

        if (choice == 'y') {
            selectedContainers.push_back(container);
            
        }
        }
    }

}

void sortOffloadLoad(std::vector<Container>& selectedContainers) {
    
    std::cout << "Sorted Containers for Offloading/Loading:" << std::endl;
    for (const auto& sortedContainer : selectedContainers) {
        std::cout << "Location: [" << sortedContainer.getlocationX() << "," << sortedContainer.getlocationY() << "], Weight: " << sortedContainer.getWeight() << ", Description: " << sortedContainer.getDescription() << std::endl;
    }
}






















































//_________________________________________________________________________________________________________
int main() {
            std::ifstream inputFile("/Users/jeff/Desktop/cs179m/ShipCase1.txt");

        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file." << std::endl;
        }
        std::vector<Container> selectedContainers;
        std::vector<Container> containers;
        sortOffloadLoad(selectedContainers);
        

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            char openBracket, closeBracket, openBrace, closeBrace, comma;
            unsigned int row, column;
            int weight;
            std::string description;

            if (iss >> openBracket >> row >> comma >> column >> closeBracket >> comma >> openBrace >> weight >> closeBrace >> comma >> description) {
                containers.emplace_back(row, column, weight, description);
            } 
        }
        inputFile.close();
        chooseContainers(containers, selectedContainers);
        for (const auto& selectedContainer : selectedContainers) {
        std::cout << "Choosed: " <<"Location: [" << selectedContainer.getlocationX() << "," << selectedContainer.getlocationY() << "], Weight: " << selectedContainer.getWeight() << ", Description: " << selectedContainer.getDescription() << std::endl;
    }



    return 0;
}

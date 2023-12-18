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

// parse
struct Container {
    int locationX, locationY;
    int weight;
    std::string name;
};

bool compareByWeight(const Container& a, const Container& b) {
    return a.weight > b.weight;
}

void SIFT(std::vector<Container>& containers) {
    // sort containers by weight
    std::sort(containers.begin(), containers.end(), compareByWeight);

    std::vector<std::pair<int, int>> slotSequence = {
        {1, 6}, {1, 7}, {1, 5}, {1, 8}, {1, 4}
    };

    
    for (size_t i = 0; i < containers.size(); ++i) {
        if (i < slotSequence.size()) {
            containers[i].locationX = slotSequence[i].first;
            containers[i].locationY = slotSequence[i].second;
        }
    }
}


// Parsing function for the container data
std::vector<Container> parseFile(const std::string& filePath) {
    std::vector<Container> containers;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        char delimiter;
        Container c;

        // Parse location
        ss >> delimiter >> c.locationX >> delimiter >> c.locationY >> delimiter;

        // Skip to the next delimiter '{'
        ss.ignore(std::numeric_limits<std::streamsize>::max(), '{');

        // Parse weight
        ss >> c.weight;

        // Skip to the next delimiter ','
        ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');

        // Parse container name or status
        std::getline(ss, c.name, '\n');
        c.name.erase(c.name.find_last_not_of(" \n\r\t")+1);

        // Skip entries with 'NAN' as they represent invalid locations
        if (c.name == " NAN") {
            continue;
        }

        // Handle 'UNUSED' entries
        if (c.name == "UNUSED") {
            c.weight = 0;
        }

        containers.push_back(c);
    }

    return containers;
}

using Ship = std::vector<std::vector<int>>;

const int ROWS = 8;
const int COLS = 12;
//const int MAX_CONTAINERS = 7;

//using Ship = std::vector<std::vector<int>>;

struct State {
    Ship ship;
    int cost;
    std::string moves;
};

struct CompareState {
    bool operator()(const State& a, const State& b) const {
        return a.cost > b.cost;
    }
};


double calculateBalanceRatio(const std::vector<std::vector<int>>& ship) {
    // an extra function - for testing purpose
    int leftMass = 0, rightMass = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS / 2; ++j) {
            leftMass += ship[i][j];
        }
        for (int j = COLS / 2; j < COLS; ++j) {
            rightMass += ship[i][j];
        }
    }
    return (double)std::min(leftMass, rightMass) / std::max(leftMass, rightMass);
}

bool isBalanced(const Ship& ship) { //check if the ship is balanced (i.e. min(L,R)/max(L,R)>=.9)
    int leftMass = 0, rightMass = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS / 2; ++j) {
            leftMass += ship[i][j];
        }
        for (int j = COLS / 2; j < COLS; ++j) {
            rightMass += ship[i][j];
        }
    }
    return (double)std::min(leftMass, rightMass) / std::max(leftMass, rightMass) >= 0.9;
}

bool canBeBalanced(std::vector<std::vector<int>>& ship) { //check if the ship can be balanced/ if cant, sift needed
    std::vector<int> containers;
    for (const auto& row : ship) {
        containers.insert(containers.end(), row.begin(), row.end());
    }

    std::sort(containers.begin(), containers.end());

    do {
        std::vector<std::vector<int>> tempShip(ROWS, std::vector<int>(COLS, 0));
        for (int i = 0, k = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j, ++k) {
                tempShip[i][j] = containers[k];
            }
        }

        if (calculateBalanceRatio(tempShip) >= 0.9) {
            return true; // can be balanced
        }
    } while (std::next_permutation(containers.begin(), containers.end()));

    return false; // cannot be balanced. -> SIFT
}

int manhattanDistance(int r1, int c1, int r2, int c2) {
    return std::abs(r1 - r2) + std::abs(c1 - c2);
}

int calculateHeuristic(const State& state) {
    int leftMass = 0, rightMass = 0;
    std::vector<int> rowImbalance(ROWS, 0); // to store imbalance per row

    // calculate total mass on each side and row imbalance
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int weight = state.ship[i][j];
            if (j < COLS / 2) {
                leftMass += weight;
                rowImbalance[i] -= weight; // negative for left side
            } else {
                rightMass += weight;
                rowImbalance[i] += weight; // positive for right side
            }
        }
    }

    int totalWeightedDistance = 0;
    
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int weight = state.ship[i][j];
            if (weight != 0) {
                int targetCol = leftMass > rightMass ? (COLS - 1) - j : j; // target column on the other side
                int distance = std::abs(targetCol - j);
                totalWeightedDistance += distance * weight;

                // add extra cost for rows with high imbalance
                if (std::abs(rowImbalance[i]) > (leftMass + rightMass) / ROWS) {
                    totalWeightedDistance += distance * weight; 
                }
            }
        }
    }

    return totalWeightedDistance;
}



bool isWithinBounds(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
} 


bool canMoveContainer(const Ship& ship, int row, int col) {
    // check if position is valid and if there is a container to move
    if (!isWithinBounds(row, col) || ship[row][col] == 0) return false;
    // check if there is no container above
    return row == 0 || ship[row - 1][col] == 0;
}


std::vector<State> getCraneNextStates(const State& currentState) {
    std::vector<State> nextStates;
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (canMoveContainer(currentState.ship, r, c)) {
                std::vector<std::pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};  
                for (auto& dir : directions) {
                    int newR = r + dir.first;
                    int newC = c + dir.second;
                    // check if new position is valid
                    if (isWithinBounds(newR, newC) && currentState.ship[newR][newC] == 0) {
                        // we don't want containers in mid air
                        if (dir.first != 1 || (newR == ROWS - 1 || currentState.ship[newR + 1][newC] != 0)) {
                            Ship newShip = currentState.ship;
                            std::swap(newShip[r][c], newShip[newR][newC]);
                            int moveCost = 1; 

                            // new coordinate system [1,1] is bottom-left
                            std::string moveDescription = "Move container from (" 
                                                          + std::to_string(ROWS - r) + "," + std::to_string(c + 1) 
                                                          + ") to (" + std::to_string(ROWS - newR) + "," + std::to_string(newC + 1) + ")";
                            nextStates.push_back({newShip, currentState.cost + moveCost, currentState.moves + " | " + moveDescription});
                        }
                    }
                }
            }
        }
    }
    return nextStates;
}

std::vector<std::vector<int>> shipGridFromManifest(const std::string& filePath) {
    std::vector<Container> containers = parseFile(filePath);
    Ship ship(8, std::vector<int>(12, 0)); 

    for (const auto& container : containers) {
        int row = 7 - (container.locationX - 1); 
        int col = container.locationY - 1;
        if (row >= 0 && row < 8 && col >= 0 && col < 12) {
            if (container.name == "NAN") {
             //   ship[row][col] = -1; // represent 'NAN' with -1 - not working :(
                // maybe not a good idea since it can effect other functions (balancing calculation)
                continue;
            } else {
                ship[row][col] = container.weight;
            }
        }
    }

    std::cout << "Ship Grid:\n";
    for (const auto& row : ship) {
        for (int weight : row) {
            if (weight == -1) {
                std::cout << "NAN\t"; // Print 'NAN' for -1 values
            } else {
                std::cout << weight << "\t";
            }
        }
        std::cout << "\n";
    }
    return ship;
}
   
int main() {
    const std::string filePath = "C:\\Users\\Jina\\OneDrive\\Desktop\\cs179\\ShipCase1.txt";
    Ship ship = shipGridFromManifest(filePath);
/*
    // display initial ship grid
    std::cout << "Ship Grid:\n";
    for (const auto& row : ship) {
        for (int weight : row) {
            std::cout << weight << "\t";
        }
        std::cout << "\n";
    }*/

    double balanceRatio = calculateBalanceRatio(ship);
    std::cout << "Current balance ratio: " << balanceRatio << "\n";

    if (balanceRatio >= 0.9) {
        std::cout << "The ship is balanced.\n";
    } else if (canBeBalanced(ship)) {
        std::cout << "The ship can be balanced by rearranging the containers. Finding optimal sequence of moves...\n";
        std::priority_queue<State, std::vector<State>, CompareState> pq;
        pq.push({ship, 0, "Start"});

        while (!pq.empty()) {
            State currentState = pq.top();
            pq.pop();

            if (isBalanced(currentState.ship)) {
                std::cout << "Balanced ship found with cost: " << currentState.cost << "\n";
                std::cout << "Moves: " << currentState.moves << "\n";
                break;
            }

            std::vector<State> nextStates = getCraneNextStates(currentState);
            for (const State& nextState : nextStates) {
                pq.push(nextState);
            }
        }
      
   } else {
        std::cout << "SIFT operation needed.\n";

       
        std::vector<Container> containers;
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (ship[i][j] > 0) {  // assuming positive values are valid containers
                    Container c;
                    c.locationX = ROWS - i;  
                    c.locationY = j + 1;
                    c.weight = ship[i][j];
                    c.name = "Container_" + std::to_string(i) + "_" + std::to_string(j);
                    containers.push_back(c);
                }
            } //for sorting and rearranging the containers
        }
        

        SIFT(containers);

        // resetting the grid
        for (auto &row : ship) {
            std::fill(row.begin(), row.end(), 0);
        }
       
        // repopulating the grid
        for (const auto &c : containers) {
            int row = ROWS - c.locationX;  
            int col = c.locationY - 1;
            if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                ship[row][col] = c.weight;
            }
        }

        std::cout << "Ship Grid after SIFT:\n";
        for (const auto& row : ship) {
            for (int weight : row) {
                std::cout << weight << "\t";
            }
            std::cout << "\n";
        }
    }
    return 0;
}
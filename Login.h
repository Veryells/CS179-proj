#ifndef EMPLOYEE_DB_H
#define EMPLOYEE_DB_H

#include <string>
#include <unordered_map>
#include <ctime>

using namespace std;

class Employee_DB
{
    private: 
        unordered_map<string, double> db;
        time_t start, end, total;


    public:
        Employee_DB(/*file*/);
        ~Manifest();

        void placeContainer(int x, int y, pair<int, string> c);
        void moveContainer(int xfrom, int yfrom, int xto, int yto);
        void deleteContainer(int x, int y);
        pair<int, string> getContainer(int x, int y);
        void outputNewManifest();
};

#endif
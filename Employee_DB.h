#ifndef EMPLOYEE_DB_H
#define EMPLOYEE_DB_H

#include <string>
#include <unordered_map>
#include <ctime>
#include <chrono>

using namespace std;

class Employee_DB
{
    private: 
        unordered_map<string, double> db;
        time_t start, end, total;
        string curr_employee;


    public:
        Employee_DB(/*file*/);
        ~Employee_DB();

        void Initial_logIn(string name);
        void logIn(string name);
};

#endif
#ifndef EMPLOYEE_DB_H
#define EMPLOYEE_DB_H

#include <string>
#include <unordered_map>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

class Employee_DB
{
    private: 
        const char* employeeFile = "Data/employeeDB.txt";
        unordered_map<string, double> db;
        chrono::system_clock::time_point start;
        string curr_employee;


    public:
        Employee_DB();
        //~Employee_DB();

        void Initial_logIn(string name);
        void logIn(string name);
        void update_file();
        string get_currEmployee();
};

#endif
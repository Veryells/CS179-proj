#include "Employee_DB"

EmployeeDB::EmployeeDB
{
//File open
//place in unordered map
};


void Initial_logIn(string name)
{
    start_t = chrono::system_clock::now();
    if(/*exists in unordered map*/) {
        curr_employee = name;
    } else {
        /*create employee in unordered map set 0*/
    }
}

void logIn(string name)
{
    end = chrono::system_clock::now();
    total = end - start_t;
    /*unordered map["curr_employee"] += total_t*/
    if(/*string exists in unordered map*/) {
        curr_employee = name;
    } else {
        /*create employee in unordered map set 0*/
    }
    start_t = chorno::system_clock::now();
}
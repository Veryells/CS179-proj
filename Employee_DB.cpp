#include "Employee_DB.h"

Employee_DB::Employee_DB(/*file*/)
{
//File open
//place in unordered map
};


void Initial_logIn(string name)
{
    start = chrono::system_clock::now();
    if(/*exists in unordered map*/) {
        curr_employee = name;
    } else {
        /*create employee in unordered map set 0*/
    }
}

void logIn(string name)
{
    end = chrono::system_clock::now();
    total = end - start;
    /*unordered map["curr_employee"] += total_t*/
    if(/*string exists in unordered map*/) {
        curr_employee = name;
    } else {
        /*create employee in unordered map set 0*/
    }
    start = chorno::system_clock::now();
}
#ifndef LOGS_H
#define LOGS_H
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

class Logs
{
    private:
        const char* logFile = "Data/Logs.txt";
        ofstream outputFile;

    public:
        Logs(); 
        ~Logs();

        void printToLogs(string s);

};

#endif
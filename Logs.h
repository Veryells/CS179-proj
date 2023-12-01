#ifndef LOGS_H
#define LOGS_H
#include <string>
#include <fstream>

using namespace std;

class Logs
{
    private:
        const string logFile = "Logs/Logs.txt";
        ofstream outputFile;

    public:
        Logs(); 
        ~Logs();

        void printToLogs(string s);

};

#endif
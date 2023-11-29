#ifndef LOGS_H
#define LOGS_H

using namespace std;

class Logs
{
    private:
        const string logFile = "Logs/Logs.txt";
        ofstream outputFile;

    public:
        Logs(); 
        ~Logs();

        void printToLogs(std::string s);

};

#endif
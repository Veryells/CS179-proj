#include "Logs.h"

using namespace std;

//Logs constructor
//Checks if file exists then opens
Logs::Logs()
{
    ifstream file(logFile);

    if(!file.good()) 
    {
        file.close();
        outputFile = ofstream(logFile);
    } 
}

//Logs destructor
//Just closes file
Logs::~Logs()
{
    outputFile.close();
}

//prints to logs
//gets gmt time then converts to utc-8
//places time then string into logs
void Logs::printToLogs(string s)
{
    time_t curr_time = time(NULL);

    tm *tm_gmt = localtime(&curr_time);
    //tm_gmt->tm_hour -= 8;                   // I dunno if this works
    outputFile << 1 + tm_gmt->tm_mon<< "/"  //?
            << tm_gmt->tm_mday<< "/"
            << (1900 + tm_gmt->tm_year) / 100<< " "
            << tm_gmt->tm_hour << ":" 
            << tm_gmt->tm_min << ":"
            << tm_gmt->tm_sec << s << endl;
}
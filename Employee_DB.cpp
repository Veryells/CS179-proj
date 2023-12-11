#include "Employee_DB.h"

using namespace std;

Employee_DB::Employee_DB()
{
    ifstream file(employeeFile);

    if(file.is_open()) 
    {
        string temp_name, temp_num, line;
        size_t startPos, endPos, spacePos;

        //get content from employee file 
        while (getline(file, line)) {
            // get from [ to ]
            startPos = line.find('[');
            endPos = line.find(']');

            //extract between [ to ]
            temp_name = line.substr(startPos + 1, endPos - startPos - 1);

            //get space position then get number after
            spacePos = line.find(' ', endPos);
            temp_num = line.substr(spacePos + 1);
            db[temp_name] = stod(temp_num); //convert number to double
            }
        file.close();
    } else {
        cout << "No Employee file found!" << endl;
        ofstream newFile(employeeFile);
        if (newFile.is_open()) {
            cout << "File created successfully." << std::endl;
            newFile.close();
            std::cout << "File closed." << std::endl;
        }
    }
}

void Employee_DB::Initial_logIn(string name)
{
    start = chrono::system_clock::now();
    if(db.count(name) > 0) {
        curr_employee = name;
    } else {
        db[name] = 0.0;
        curr_employee = name;
    }
}

void Employee_DB::logIn(string name)
{
    //gets current end time since start and convert to double
    auto end = start.time_since_epoch();
    double hours = chrono::duration_cast<std::chrono::hours>(end).count();
    db[curr_employee] += hours;

    //check if inputted employee exists in map and create if it doesn't
    if(db.count(name) > 0) {
        curr_employee = name;
    } else {
        db[name] = 0.0;
        curr_employee = name;
    }

    //set start time back to now
    start = chrono::system_clock::now();
}

//Just completely overwrites the file with the db lmao
void Employee_DB::update_file()
{
    ofstream outputFile(employeeFile, ios::trunc);
    //check if file exists then write
    if (!outputFile.is_open()) {
        cout << "Failed to open the file for writing." << std::endl;
        return;
    } else {
        for (const auto& pair : db) {
            outputFile << "[" << pair.first << "] " << pair.second << std::endl;
        }
    }

    cout << "File updated successfully." << std::endl;
}
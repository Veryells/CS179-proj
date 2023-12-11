#include "Manifest.h"

using namespace std;

//Manifest constructor
Manifest::Manifest(/*file path*/)
{
    //store manifest name
    manifName = /*manifest name*/;

    string line, weight, container_name;
    size_t openBracePos, closeBracePos, secondCommaPos;
    int x = 1, y = 1, run = 0;
    while (getline(/*file*/, line)) {
        // Find the position of { and }
        openBracePos = line.find('{');
        closeBracePos = line.find('}');

        // Find the position of the second comma ','
        secondCommaPos = line.find(',', line.find(',') + 1);

        // Check if all positions are found
        if (openBracePos != std::string::npos &&
            closeBracePos != std::string::npos &&
            secondCommaPos != std::string::npos) {
            // Extract the number between '{' and '}'
            weight = line.substr(openBracePos + 1, closeBracePos - openBracePos - 1);

            // Extract the string after the second comma
            container_name = line.substr(secondCommaPos + 1);

            //increment every 8 runs for x and y  resets after 12
            if (run % 8 == 0 && run > 0) {++x;}
            if (y == 13) {y = 1;}

            pair<int, string> myPair = make_pair(stoi(weight), container_name);
            manif[x][y] = myPair;
            ++y;
        }
    }
}

Manifest::~Manifest()
{
    /*close file*/
}

void Manifest::placeContainer(int x, int y, pair<int, string> c)
{
    manif[x][y] = c;
}

void Manifest::moveContainer(int xfrom, int yfrom, int xto, int yto)
{
    pair<int, string> temp = manif[xfrom][yfrom];
    placeContainer(xto, yto, temp);
}

void Manifest::deleteContainer(int x, int y)
{
    pair<int, string> temp (0, "UNUSED");
    manif[x][y] = temp;
}

pair<int, string> Manifest::getContainer(int x, int y) 
{
    return manif[x][y];
}

//Prints out new manifest to file
void Manifest::outputNewManifest()
{
    pair<int, string> temp;
    ofstream newManifest(/*string name of newmanifest*/);
    if (newManifest.is_open()) {   
        for(int x = 0; x < 8; x++) {
            for(int y = 0; y < 12; y++) {
                temp = manif[x][y];
                newManifest << '[' << setw(2) << setfill('0') << x << ',' 
                    << setw(2) << setfill('0') << y << "], {"
                    << setw(5) << setfill('0') << temp.first << "}, "
                    << temp.second << '\n';
            }
        }
    }
};
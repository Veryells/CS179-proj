#include "Manifest.h"
#include <fstream>
#include <iomanip>
using namespace std;

//Manifest constructor
Manifest::Manifest(/*file*/)
{

}

Manifest::~Manifest()
{
    /*close file*/
};

void placeContainer(int x, int y, int x1, string y1)
{
    pair<int, string> temp (x1, y1);
    manif[x][y] = temp;
};

void moveContainer(int xfrom, int yfrom, int xto, int yto)
{
    pair<int, string> temp = manif[xfrom][yfrom];
    placeContainer(xto, yto, temp.first, temp.second);
};

void deleteContainer(int x, int y)
{
    pair<int, string> temp (0, "UNUSED");
    manif[x][y] = temp;
};

pair<int, string> getContainer(int x, int y) 
{
    return manif[x][y];
};

//Prints out new manifest to file
void updateNewManifest()
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
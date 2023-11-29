#ifndef MANIFEST_H
#define MANIFEST_H

#include <utility>

using namespace std;

class Manifest
{
    private: 
        pair<int, string> manif[5][8];

    public:
        Manifest(/*file*/);
        ~Manifest();

        void placeContainer(int x, int y, pair<int, string> c);
        void moveContainer(int xfrom, int yfrom, int xto, int yto);
        void deleteContainer(int x, int y);
        pair<int, string> getContainer(int x, int y) {return manif[x][y]};
        void createNewManifest();
};

#endif
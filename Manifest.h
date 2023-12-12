#ifndef MANIFEST_H
#define MANIFEST_H

#include <utility>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

class Manifest
{
    private:
        pair<int, string> manif[8][12];
        string manifName;

    public:
        Manifest(string filepath);
        ~Manifest();

        void placeContainer(int x, int y, pair<int, string> c);
        void moveContainer(int xfrom, int yfrom, int xto, int yto);
        void deleteContainer(int x, int y);
        pair<int, string> getContainer(int x, int y);
        void outputNewManifest();
};

#endif
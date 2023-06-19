#ifndef SCULPTOR_H
#define SCULPTOR_H
#include "Voxel.hpp"

class Sculptor {

public:

    Voxel ***v;

    int nx,ny,nz;

    Sculptor(int _nx, int _ny, int _nz);

    ~Sculptor();

    void writeOFF(const char* filename);
};
#endif

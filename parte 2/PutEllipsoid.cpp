#include "PutEllipsoid.hpp"
#include "Voxel.hpp"
#include "Sculptor.hpp"
#include <iostream>

PutEllipsoid::PutEllipsoid(int x, int y, int z, int rx, int ry, int rz, float r, float g, float b, float a)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
};

void PutEllipsoid::Draw(Sculptor& Sculptor)
{
    int i = -rx;
    int j = -ry;
    int k = -rz;

    if(rx == 0 || ry == 0 || rz == 0)
    {
        std::cerr << "Erro: elipsoide degenerada \n";
        return;
    }

    do{
        // verificação para garantir que as coordenadas estejam dentro dos limites do Sculptor. verificações interiores são análogas
        if(x + i >= 0 && x + i < Sculptor.nx)
        {
            j = -ry;
            do{
                if(y + j >= 0 && y + j < Sculptor.ny)
                {
                    k = -rz;
                    do{
                        if(z + k >= 0 && z + k < Sculptor.nz)
                        {
                            if(((i*i)/(float)(rx*rx)) + ((k*k)/(float)(rz*rz)) + ((j*j)/(float)(ry*ry)) <= 1)
                            {
                                Sculptor.v[x+i][y+j][z+k] = Voxel{r, g, b, a, true};
                            }
                        }
                        k++;
                    }
                    while (k <= rz);
                }
                j++;
            }
            while (j <= ry);
        }
        i++;
    }
    while (i <= rx);
}

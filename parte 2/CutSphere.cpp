#include "CutSphere.hpp"
#include "Voxel.hpp"

CutSphere::CutSphere(int x, int y, int z, int raio)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->raio = raio;
};

void CutSphere::Draw(Sculptor& Sculptor)
{
    // Raciocínio análogo ao método putSphere
    int i = -raio;
    int j = -raio;
    int k = -raio;

    do{
        if(x + i >= 0 && x + i < Sculptor.nx)
        {
            j = -raio;
            do{
                if(y + j >= 0 && y + j < Sculptor.ny)
                {
                    k = -raio;
                    do{
                        if(z + k >= 0 && z + k < Sculptor.nz)
                        {
                            if(i*i + j*j +k*k <= raio*raio)
                            {
                                Sculptor.v[x+i][y+j][z+k].show = false;
                            }
                        }
                        k++;
                    }
                    while (k <= raio);
                }
                j++;
            }
            while (j <= raio);
        }
        i++;
    }
    while (i <= raio);
}

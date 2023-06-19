#include "PutSphere.hpp"
#include "Voxel.hpp"
#include "Sculptor.hpp"

PutSphere::PutSphere(int x, int y, int z, int raio, float r, float g, float b, float a)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->raio = raio;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
};

void PutSphere::Draw(Sculptor& Sculptor)
{
    // iterar de -raio até raio para evitar o deslocamento na equação da esfera, o que permite simplificações
    int i = -raio;
    int j = -raio;
    int k = -raio;

    do{
        // verificação para garantir que as coordenadas estejam dentro dos limites do Sculptor. verificações interiores são análogas
        if(x + i >= 0 && x + i < Sculptor.nx)
        {
            j = -raio;
            do{
                if(y + j >= 0 && y + j <Sculptor.ny)
                {
                    k = -raio;
                    do{
                        if(z + k >= 0 && z + k < Sculptor.nz)
                        {
                            if(i*i + j*j +k*k <= raio*raio)
                            {
                                Sculptor.v[x+i][y+j][z+k] = Voxel{r, g, b, a, true};
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

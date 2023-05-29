#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "Sculptor.hpp"

// Implementação do construtor da classe

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    if (_nx < 1 || _ny < 1 || _nz < 1)
    {
        std::cerr << "Erro: dimensões invalidas (<1) \n";
        std::exit(1);
    }

    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;

    this->v = new Voxel**[_nx];
    Voxel** vd1 = new Voxel*[_nx*_ny];
    Voxel* vd2 = new Voxel[_nx*_ny*_nz];

    for (int i=0; i<nx; i++)
    {
        this->v[i] = vd1 + (i*_ny);

        for (int j=0; j<ny; j++)
        {
            this->v[i][j] = vd2 + i*_ny*_nz + j*_nz;

            for (int k=0; k<ny; k++)
            {
                this->v[i][j][k] = Voxel{0.0, 0.0, 0.0, 0.0, false};
            }
        }
    }

    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 0;
}

// Implementação do destrutor da classe

Sculptor::~Sculptor()
{
    delete[] this->v[0][0];
    delete[] this->v[0];
    delete[] this->v;
};

// Implementação do método setColor

void Sculptor::setColor(float r, float g, float b, float a)
{
    if (r > 1 || g > 1 || b > 1 || a > 1 || r < 0 || g < 0 || b < 0 || a < 0)
    {
        std::cerr << "Valores de cores invalidos (rgb ou 'a' fora do intervalo 0 - 1) \n";
        return;
    }
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

// Implementação do método putVoxel

void Sculptor::putVoxel(int x, int y, int z)
{
    if (x >= 0 && y >= 0 && z >= 0 && x < nx && y < ny && z < nz)
    {
        v[x][y][z] = Voxel{r, g, b, a, true};
    }
}

// Implementação do método cutVoxel

void Sculptor::cutVoxel(int x, int y, int z)
{
    if (x >= 0 && y >= 0 && z >= 0 && x < nx && y < ny && z < nz)
    {
        v[x][y][z].show = false;
    }
}

// Implementação do método putBox

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    int i = x0;
    int j = y0;
    int k = z0;

    // O do-while mais externo percorre a coordenada x a partir de x0, incrementando se x1 > x0 e decremetando caso x0 > x1
    // De maneira análoga ocorre para os do-while internos

    do{
        if(i>=0 && i< nx)
        {
            j = y0;
            do{
                if(j >= 0 && j < ny)
                {
                    k = z0;
                    do{
                        if(k >= 0 && k < nz)
                        {
                            putVoxel(i,j,k);
                        }
                        (z1 >= z0) ? k++ : k--;
                    }
                    while ((z1 >= z0) ? k <= z1 : k >= z1);
                }
                (y1 >= y0) ? j++ : j--;
            }
            while ((y1 >= y0) ? j <= y1 : j >= y1);
        }
        (x1 >= x0) ? i++ : i--;
    }
    while ((x1 >= x0) ? i <= x1 : i >= x1);
}

// Implementação do método cutBox

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    int i = x0;
    int j = y0;
    int k = z0;

    // Raciocínio análogo ao dos do-while do método putBox

    do{
        if(i >= 0 && i < nx)
        {
            j = y0;
            do{
                if(j >= 0 && j < ny)
                {
                    k = z0;
                    do{
                        if(k >= 0 && k < nz)
                        {
                            cutVoxel(i,j,k);
                        }
                        (z1 >= z0) ? k++ : k--;
                    }
                    while ((z1 >= z0) ? k <= z1 : k >= z1);
                }
                (y1 >= y0) ? j++ : j--;
            }
            while ((y1 >= y0) ? j <= y1 : j >= y1);
        }
        (x1 >= x0) ? i++ : i--;
    }
    while ((x1 >= x0) ? i <= x1 : i >= x1);
}

// Implementação do método putSphere

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    // iterar de -radius até radius para evitar o deslocamento na equação da esfera, o que permite simplificações
    int i = -radius;
    int j = -radius;
    int k = -radius;

    do{
        // verificação para garantir que as coordenadas estejam dentro dos limites do Sculptor. verificações interiores são análogas
        if(xcenter + i >= 0 && xcenter + i < nx)
        {
            j = -radius;
            do{
                if(ycenter + j >= 0 && ycenter + j< ny)
                {
                    k = -radius;
                    do{
                        if(zcenter + k >= 0 && zcenter + k < nz)
                        {
                            if(i*i + j*j + k*k <= radius*radius)
                                {
                                    putVoxel(xcenter + i,ycenter + j,zcenter + k);
                                }
                        }
                        k++;
                    }
                    while (k <= radius);
                }
                j++;
            }
            while (j <= radius);
        }
        i++;
    }
    while (i <= radius);
}

// Implementação do método cutSphere

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    // Raciocínio análogo ao método putSphere
    int i = -radius;
    int j = -radius;
    int k = -radius;

    do{
        if(xcenter + i >= 0 && xcenter + i < nx)
        {
            j = -radius;
            do{
                if(ycenter + j >= 0 && ycenter + j < ny)
                {
                    k = -radius;
                    do{
                        if(zcenter + k >= 0 && zcenter + k < nz)
                        {
                            if(i*i + j*j + k*k <= radius*radius)
                            {
                                cutVoxel(xcenter + i,ycenter + j,zcenter + k);
                            }
                        }
                        k++;
                    }
                    while (k <= radius);
                }
                j++;
            }
            while (j <= radius);
        }
        i++;
    }
    while (i <= radius);
}

// Implementação do método putEllipsoid

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    int i = - rx;
    int j = - ry;
    int k = - rz;

    if(rx == 0 || ry == 0 || rz == 0)
    {
        std::cerr << "Erro: elipsoide degenerada \n";
        return;
    }
    do{
        // verificação para garantir que as coordenadas estejam dentro dos limites do Sculptor. verificações interiores são análogas
        if(xcenter + i >= 0 && xcenter + i < nx)
        {
            j = -ry;
            do{
                if(ycenter + j >= 0 && ycenter + j < ny)
                {
                    k = -rz;
                    do{
                        if(zcenter + k >= 0 && zcenter + k < nz)
                        {
                            if(((i*i)/(float)(rx*rx)) + ((j*j)/(float)(ry*ry)) + ((k*k)/(float)(rz*rz)) <= 1)
                                {
                                    putVoxel(xcenter + i,ycenter + j,zcenter + k);
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

// Implementação do método cutEllipsoid

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    // Raciocínio análogo ao método putEllipsoid
    int i = -rx;
    int j = -ry;
    int k = -rz;

    if( rx == 0 || ry == 0 || rz == 0)
    {
        std::cerr << "Erro: elipsoide degenerada \n";
        return;
    }
    do{
        if(xcenter + i >= 0 && xcenter + i < nx)
        {
            j = -ry;
            do{
                if(ycenter + j >= 0 && ycenter + j < ny)
                {
                    k = -rz;
                    do{
                        if(zcenter + k >= 0 && zcenter + k < nz)
                        {
                            if(((i*i)/(float)(rx*rx)) + ((j*j)/(float)(ry*ry)) + ((k*k)/(float)(rz*rz)) <= 1)
                            {
                                cutVoxel(xcenter + i,ycenter + j,zcenter + k);
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

// Implementação do método writeOFF

void Sculptor::writeOFF(const char* filename)
{
    std::ofstream arquivo(filename, std::ios::out);

    if (arquivo.is_open() == false)
    {
        std::cerr << "Falha ao abrir o arquivo \n";
        std::exit(1);
    }

    // Indicando que o formato do arquivo é OFF
    arquivo << "OFF" << std::endl;

    int contagem = 0;

    // Percorrendo cada Voxel
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                // Verifica se o voxel está como visível
                if (v[i][j][k].show == true)
                {
                    // Verifica se o voxel atual não está na borda
                    if (i != 0 && i != nx-1 && j != 0 && j != ny-1 && k != 0 && k != nz-1)
                    {
                        // Verifica se pelo menos um dos voxels vizinhos está invisível
                        if ( (v[i+1][j][k].show == false) || (v[i-1][j][k].show == false) || (v[i][j+1][k].show == false) || (v[i][j-1][k].show == false) || (v[i][j][k+1].show == false) || (v[i][j][k-1].show == false))
                        {
                            contagem += 1;
                        }
                    }
                    else
                    {
                        contagem += 1;
                    }
                }
            }
        }
    }

    // Segunda linha do arquivo, NVertices; NFaces; NArestas
    arquivo << contagem*8 << " " << contagem*6 << " " << 0 << std::endl;

    // Percorrendo cada Voxel
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                // Verifica se o voxel está como visível
                if (v[i][j][k].show == true)
                {
                    // Verifica se o voxel atual não está na borda
                    if (i != 0 && i != nx-1 && j != 0 && j != ny-1 && k != 0 && k != nz-1)
                    {
                        // Verifica se pelo menos um dos voxels vizinhos está invisível
                        if ( (v[i+1][j][k].show == false) || (v[i-1][j][k].show == false) || (v[i][j+1][k].show == false) || (v[i][j-1][k].show == false) || (v[i][j][k+1].show == false) || (v[i][j][k-1].show == false))
                        {
                            // Coordenadas dos vértices do Voxel atual
                            arquivo << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                            arquivo << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                            arquivo << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                            arquivo << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                            arquivo << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                            arquivo << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                            arquivo << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                            arquivo << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                        }
                    }
                    // Se estiver na borda
                    else
                    {
                        // Coordenadas dos vértices do Voxel atual
                        arquivo << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                        arquivo << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                        arquivo << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                        arquivo << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                        arquivo << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                        arquivo << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                        arquivo << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                        arquivo << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                    }
                }
            }
        }
    }

    contagem = 0;

    // Percorrendo cada Voxel
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                // Verifica se o voxel está como visível
                if (v[i][j][k].show == true)
                {
                    // Verifica se o voxel atual não está na borda
                    if (i != 0 && i != nx-1 && j != 0 && j != ny-1 && k != 0 && k != nz-1)
                    {
                        // Verifica se pelo menos um dos voxels vizinhos está invisível
                        if ( (v[i+1][j][k].show == false) || (v[i-1][j][k].show == false) || (v[i][j+1][k].show == false) || (v[i][j-1][k].show == false) || (v[i][j][k+1].show == false) || (v[i][j][k-1].show == false))
                        {
                            // Definições das faces do voxel atual
                            arquivo << 4 << " " << contagem*8 << " " << contagem*8 +3 << " " << contagem*8 +2 << " " << contagem*8 +1 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                            arquivo << 4 << " " << contagem*8 +4 << " " << contagem*8 +5 << " " << contagem*8 +6 << " " << contagem*8 +7 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                            arquivo << 4 << " " << contagem*8 << " " << contagem*8 +1 << " " << contagem*8 +5 << " " << contagem*8 +4 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                            arquivo << 4 << " " << contagem*8 << " " << contagem*8 +4 << " " << contagem*8 +7 << " " << contagem*8 +3 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                            arquivo << 4 << " " << contagem*8 +3 << " " << contagem*8 +7 << " " << contagem*8 +6 << " " << contagem*8 +2 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                            arquivo << 4 << " " << contagem*8 +1 << " " << contagem*8 +2 << " " << contagem*8 +6 << " " << contagem*8 +5 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                            contagem += 1;
                        }
                    }
                    // Se estiver na borda
                    else
                    {
                        // Definições das faces do voxel atual
                        arquivo << 4 << " " << contagem*8 << " " << contagem*8 +3 << " " << contagem*8 +2 << " " << contagem*8 +1 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                        arquivo << 4 << " " << contagem*8 +4 << " " << contagem*8 +5 << " " << contagem*8 +6 << " " << contagem*8 +7 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                        arquivo << 4 << " " << contagem*8 << " " << contagem*8 +1 << " " << contagem*8 +5 << " " << contagem*8 +4 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                        arquivo << 4 << " " << contagem*8 << " " << contagem*8 +4 << " " << contagem*8 +7 << " " << contagem*8 +3 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                        arquivo << 4 << " " << contagem*8 +3 << " " << contagem*8 +7 << " " << contagem*8 +6 << " " << contagem*8 +2 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                        arquivo << 4 << " " << contagem*8 +1 << " " << contagem*8 +2 << " " << contagem*8 +6 << " " << contagem*8 +5 << " " << std::fixed << std::setprecision(2) << v[i][j][k].r << " " << std::fixed << std::setprecision(2) << v[i][j][k].g << " " << std::fixed << std::setprecision(2) << v[i][j][k].b << " " << std::fixed << std::setprecision(2) << v[i][j][k].a << std::endl;
                        contagem += 1;
                    }
                }
            }
        }
    }

    arquivo.close();
}

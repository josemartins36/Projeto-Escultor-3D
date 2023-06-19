#include "Sculptor.hpp"
#include "PutVoxel.hpp"
#include "CutVoxel.hpp"
#include "PutBox.hpp"
#include "CutBox.hpp"
#include "PutSphere.hpp"
#include "CutSphere.hpp"
#include "PutEllipsoid.hpp"
#include "CutEllipsoid.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>


void Filepatt(std::vector<FiguraGeometrica*>& vetobj, std::string filename, int* nx, int* ny, int* nz)
{
    std::ifstream txtfile(filename, std::ios::in);
    if (!txtfile.is_open())
    {
        std::cout << "Erro: nao foi possível abrir o arquivo" << std::endl;
        exit(1);
    }

    std::string linha;
    std::getline(txtfile, linha);
    std::istringstream dados(linha);
    std::string metodo;

    if (!(dados >> metodo))
    {
        std::cout << "Erro: linha em formato invalido" << std::endl;
        exit(2);
    }

    dados >> *nx >> *ny >> *nz;

    while (std::getline(txtfile, linha))
    {
        std::istringstream dados(linha);
        if (!(dados >> metodo))
        {
            std::cout << "Aviso: linha vazia detectada" << metodo <<std::endl;
            continue;
        }
        else
        {
            if (metodo=="putvoxel")
            {
                int x, y, z;
                float r, g, b, a;

                dados >> x >> y >> z >> r >> g >> b >> a;
                vetobj.push_back(new PutVoxel(x, y, z, r, g, b, a));
                continue;
            }
            if (metodo=="cutvoxel")
            {
                int x, y, z;

                dados >> x >> y >> z;
                vetobj.push_back(new CutVoxel(x, y, z));
                continue;
            }
            if (metodo=="putbox")
            {
                int x0, x1, y0, y1, z0, z1;

                float r, g, b, a;
                dados >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
                vetobj.push_back(new PutBox(x0, x1, y0, y1, z0, z1, r, g, b, a));
                continue;
            }
            if (metodo=="cutbox")
            {
                int x0, x1, y0, y1, z0, z1;

                dados >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
                vetobj.push_back(new CutBox(x0, x1, y0, y1, z0, z1));
                continue;
            }
            if (metodo=="putsphere")
            {
                int x, y, z, raio;

                float r, g, b, a;
                dados >> x >> y >> z >> raio >> r >> g >> b >> a;
                vetobj.push_back(new PutSphere(x, y, z, raio, r, g, b, a));
                continue;
            }
            if (metodo=="cutsphere")
            {
                int x, y, z, raio;

                dados >> x >> y >> z >> raio;
                vetobj.push_back(new CutSphere(x, y, z, raio));
                continue;
            }
            if (metodo=="putellipsoid")
            {
                int x, y, z, rx, ry, rz;

                float r, g, b, a;
                dados >> x >> y >> z >> rx >> ry >> rz >> r >> g >> b >> a;
                vetobj.push_back(new PutEllipsoid(x, y, z, rx, ry, rz, r, g, b, a));
                continue;
            }
            if (metodo=="cutellipsoid")
            {
                int x, y, z, rx, ry, rz;

                dados >> x >> y >> z >> rx >> ry >> rz;
                vetobj.push_back(new CutEllipsoid(x, y, z, rx, ry, rz));
                continue;
            }
            std::cout << "Metodo nao detectado: " << metodo << std::endl;
        }
    }
    txtfile.close();
}

int main()
{

    std::vector<FiguraGeometrica*> lista;

    int* nx = new int;
    int* ny = new int;
    int* nz = new int;

    Filepatt(lista, "exemplo.txt", nx, ny, nz);

    Sculptor teste = Sculptor(*nx, *ny, *nz);

    for (FiguraGeometrica* fig : lista){
        (*fig).Draw(teste);
        delete fig;
    }
    teste.writeOFF("exemplo.off");
    delete nx;
    delete ny;
    delete nz;
    return 0;
}

#include "Sculptor.hpp"
#include <iostream>

int main()
{
    Sculptor teste = Sculptor(100, 100, 100);

    // Criando a mesa (teste putBox & cutBox)

    teste.setColor(0.2745, 0.1765, 0.1098, 1.0);

    teste.putBox(10,20,10,20,10,20);

    teste.cutBox(10,19,11,19,10,20);

    teste.cutBox(10,19,10,20,11,19);

    // Criando a cúpula do abajur (teste putSphere & cutSphere)

    teste.setColor(0.9843, 0.9529, 0.7686, 1.0);

    teste.putSphere(31,15,15, 5);

    teste.cutSphere(28,15,15,5);

    // Criando a base do abajur

    teste.setColor(0.9216, 0.6, 0.0039, 1.0);

    teste.putBox(21,21,13,17,13,17);

    teste.putBox(21,35,15,15,15,15);

    // teste putEllipsoid & cutEllipsoid

    teste.setColor(0, 0.8, 1.0, 1.0);

    teste.putEllipsoid(35,35,35, 5, 7, 9);

    teste.cutEllipsoid(35,35,35,5, 5, 5);

    // teste putVoxel & cutVoxel

    teste.setColor(1.0, 0.0, 0.8, 1.0);

    teste.putVoxel(45,35,35);

    teste.putVoxel(47,35,35);

    teste.cutVoxel(47,35,35);

    teste.writeOFF("exemplo.off");

    return 0;
}

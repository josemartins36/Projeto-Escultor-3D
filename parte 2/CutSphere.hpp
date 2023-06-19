#include "FiguraGeometrica.hpp"

class CutSphere : public FiguraGeometrica {

private:

    int x;
    int y;
    int z;
    int raio;

public:

    CutSphere(int x, int y, int z, int raio);

    ~CutSphere();

    void Draw(Sculptor& Sculptor);
};

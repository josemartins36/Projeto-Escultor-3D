#include "FiguraGeometrica.hpp"
#include "Sculptor.hpp"

class PutSphere : public FiguraGeometrica {

private:

    int x;
    int y;
    int z;
    int raio;
    float r;
    float g;
    float b;
    float a;

public:

    PutSphere(int x, int y, int z, int raio, float r, float g, float b, float a);

    ~PutSphere();

    void Draw(Sculptor& Sculptor);
};

#include "FiguraGeometrica.hpp"
#include "Sculptor.hpp"

class PutEllipsoid : public FiguraGeometrica {

private:

    int x;
    int y;
    int z;
    int rx;
    int ry;
    int rz;
    float r;
    float g;
    float b;
    float a;

public:

    PutEllipsoid(int x, int y, int z, int rx, int ry, int rz, float r, float g, float b, float a);

    ~PutEllipsoid();

    void Draw(Sculptor& Sculptor);
};

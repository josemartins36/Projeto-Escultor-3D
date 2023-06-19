#include "FiguraGeometrica.hpp"
#include "Sculptor.hpp"

class CutEllipsoid : public FiguraGeometrica {

private:

    int x;
    int y;
    int z;
    int rx;
    int ry;
    int rz;

public:

    CutEllipsoid(int x, int y, int z, int rx, int ry, int rz);

    ~CutEllipsoid();

    void Draw(Sculptor& Sculptor);
};

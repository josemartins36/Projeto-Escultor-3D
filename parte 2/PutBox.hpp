#include "FiguraGeometrica.hpp"
#include "Sculptor.hpp"

class PutBox : public FiguraGeometrica {

private:

    int x0;
    int x1;
    int y0;
    int y1;
    int z0;
    int z1;
    float r;
    float g;
    float b;
    float a;

public:

    PutBox(int x0, int x1, int y0, int y1, int z0, int z1, float r, float g, float b, float a);

    ~PutBox();

    void Draw(Sculptor& Sculptor);
};

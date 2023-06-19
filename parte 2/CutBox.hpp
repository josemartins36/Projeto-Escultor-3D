#include "FiguraGeometrica.hpp"
#include "Sculptor.hpp"

class CutBox : public FiguraGeometrica {

private:

    int x0;
    int y0;
    int z0;
    int x1;
    int y1;
    int z1;

public:

    CutBox(int x0, int x1, int y0, int y1, int z0, int z1);

    ~CutBox();

    void Draw(Sculptor& Sculptor);
};

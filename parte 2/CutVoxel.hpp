#include "FiguraGeometrica.hpp"
#include "Sculptor.hpp"

class CutVoxel : public FiguraGeometrica {

private:

    int x;
    int y;
    int z;

public:

    CutVoxel(int x, int y, int z);

    ~CutVoxel();

    void Draw(Sculptor& Sculptor);
};

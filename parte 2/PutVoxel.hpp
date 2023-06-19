#include "FiguraGeometrica.hpp"
#include "Sculptor.hpp"

class PutVoxel : public FiguraGeometrica {

private:

    int x;
    int y;
    int z;
    float r;
    float g;
    float b;
    float a;

public:

    PutVoxel(int x, int y, int z, float r, float g, float b, float a);

    ~PutVoxel();

    void Draw(Sculptor& Sculptor);
};

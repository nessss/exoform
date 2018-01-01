#ifndef __TERRAIN_H
#define __TERRAIN_H

#include "material.h"

class Terrain {
    public:
        virtual int GetSprite() = 0;
        virtual int GetElevation() = 0;
        virtual int GetHardness() = 0;
        virtual Material GetMaterial() = 0;
}

#endif

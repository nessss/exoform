#ifndef __MATERIAL_H
#define __MATERIAL_H

#include "color.h"

class Material {
    public:
        virtual int GetWeight() = 0;
        virtual Color GetColor() = 0;
}

#endif

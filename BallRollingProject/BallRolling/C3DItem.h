#pragma once
#include "C3DPrism.h"
class C3DItem :
    public C3DPrism
{
public:
    C3DItem(VECTOR worldposi, VECTOR localposi, ST_Angle* _worldangle, ST_Angle _angle, VECTOR _size);
};


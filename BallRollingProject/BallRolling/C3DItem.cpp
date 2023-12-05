#include "C3DItem.h"


C3DItem::C3DItem(VECTOR worldposi, VECTOR localposi, ST_Angle* _worldAngle, ST_Angle _localangle, VECTOR _size)
	:C3DPrism(worldposi, localposi, _worldAngle,_localangle,_size)
{
}


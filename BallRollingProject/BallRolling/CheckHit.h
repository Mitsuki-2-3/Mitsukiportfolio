#pragma once
#include"common.h"
#include"C3DPrism.h"
#include"C3DSphere.h"
#include<math.h>
#include<cmath>


ST_CheckHit Check3DQuadrangularPrism(C3DPrism* prism, C3DSphere* sphere);

ST_CheckHit CheckFaceOfCube(C3DPrism* prism, C3DSphere* sphere);

bool AABBPrism(C3DPrism* prism, C3DSphere* sphere);

bool OBBPrism(C3DPrism* prism, C3DSphere* sphere);
//----------------------------------------------------------------------------
//
//mth_angle.cpp
//
//Copyright Е Rishi Ramraj, 2004
//----------------------------------------------------------------------------

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Inclusions
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

#include <math.h>
#include "mth_angle.h"

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Definitions
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Structures
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Class Defs
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Private Function Defs
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Private Vars
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: External Function Implementation
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

float mth_reduce_deg(float deg)
{
	deg -= (float)floor(deg/MTH_360);
	if(deg < 0)
		deg += MTH_360;
	return deg;
}
float mth_reduce_rad(float rad)
{
	rad -= (float)floor(rad/MTH_TWO_PI);
	if(rad < 0)
		rad += MTH_TWO_PI;
	return rad;
}

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: External Class Implementation
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Internal Function Implementation
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Internal Class Implementation
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//----------------------------------------------------------------------------
//mth_angle.cpp
//Copyright Е Rishi Ramraj, 2004
//----------------------------------------------------------------------------

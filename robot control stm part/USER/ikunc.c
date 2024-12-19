#include "ikunc.h"


int32_t* dof_IK(float *site , int32_t *Joint)
{
	float jt[6];
	float d1 = 488;
	float a1 = 168.8;
	float a2 = 651.761;
	float d3 = 8.299;
	float a3 = 161.824;
	float d4 = 636.120;
	
	float X = site[0]*1000;
	float Y = site[1]*1000;
	float Z = site[2]*1000 - d1;
	
	float D2 = sqrtf(d4*d4 + a3*a3);
	float theta = atan2f(a3 , d4);
	jt[0] = atan2f(Y , X)-atan2f(-d3 , sqrtf(X*X+Y*Y-d3*d3));
	
	float X1 = X - a1*cosf(jt[0]);
	float Y1 = Y - a1*sinf(jt[0]) - d3/cosf(jt[0]);
  float	D0 = sqrtf(X1*X1 + Y1*Y1) +d3*tanf(jt[0]);
	float D  = sqrtf(D0*D0 + Z*Z);
	
	float ja = atan2f(Z , D0);
	float j2a= acosf((a2*a2 + D*D - D2*D2) / (2*D*a2));
	jt[1] = -(M_PI/2 -j2a -ja);

	float j3a= acosf((a2*a2 + D2*D2 - D*D) / (2*D2*a2));
	jt[2] = j3a -M_PI/2 -theta;

	jt[3]  = 0;
	jt[4]  = (M_PI/2 - jt[2] - jt[1]);
	jt[5]  = -jt[0];	
	int i;
	for( i=0;i<6;i++)
	{
		Joint[i] = round((180000*jt[i])/M_PI);
	}
	return Joint;
}


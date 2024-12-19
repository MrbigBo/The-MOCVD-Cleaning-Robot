#ifndef __IKUNC_H
#define	__IKUNC_H

#include "stm32f10x.h"
#include <stdio.h>
#include "math.h"

#define  M_PI	3.14159265358979323846

int32_t* dof_IK(float *site , int32_t *Joint);

#endif /* __IKUNC_H */


#pragma once

#include "point.h"

typedef struct perlin_smooth
{
  int     point_count;
  double *randfloat;
  int    *perm_x;
  int    *perm_y;
  int    *perm_z;

} perlin_smooth_t;

perlin_smooth_t *perlin_smooth_new ();
void             perlin_smooth_del (perlin_smooth_t *p);
double           perlin_smooth_noise (perlin_smooth_t *p, const point3_t *point);

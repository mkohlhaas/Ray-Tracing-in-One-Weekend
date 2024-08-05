#pragma once

#include "point.h"

typedef struct perlin
{
  int     point_count;
  double *randfloat;
  int    *perm_x;
  int    *perm_y;
  int    *perm_z;

} perlin_t;

perlin_t *perlin_new ();
void      perlin_del (perlin_t *p);
double    perlin_noise (perlin_t *p, const point3_t *point, int granularity);

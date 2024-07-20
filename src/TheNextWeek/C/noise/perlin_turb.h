#pragma once

#include "math/point.h"

typedef struct perlin_turb
{
  int     point_count;
  vec3_t *randvec;
  int    *perm_x;
  int    *perm_y;
  int    *perm_z;
} perlin_turb_t;

perlin_turb_t *perlin_turb_new ();
void           perlin_turb_del (perlin_turb_t *p);
double         perlin_turb_turbulence (perlin_turb_t *p, point3_t const *point, int depth);

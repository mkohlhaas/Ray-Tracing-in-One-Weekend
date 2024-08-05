#pragma once

#include "point.h"

typedef struct perlin_phase
{
  int     point_count;
  vec3_t *randvec;
  int    *perm_x;
  int    *perm_y;
  int    *perm_z;
} perlin_phase_t;

perlin_phase_t *perlin_phase_new ();
void            perlin_phase_del (perlin_phase_t *p);
double          perlin_phase_noise (perlin_phase_t *p, point3_t const *point, int depth);

#pragma once

#include "math/point.h"

typedef struct perlin_freq
{
  int     point_count;
  double *randfloat;
  int    *perm_x;
  int    *perm_y;
  int    *perm_z;
} perlin_freq_t;

perlin_freq_t *perlin_freq_new ();
void           perlin_freq_del (perlin_freq_t *p);
double         perlin_freq_noise (perlin_freq_t *p, const point3_t *point);

#pragma once

#include "math/point.h"

typedef struct perlin_hermitian
{
  int     point_count;
  double *randfloat;
  int    *perm_x;
  int    *perm_y;
  int    *perm_z;
} perlin_hermitian_t;

perlin_hermitian_t *perlin_hermitian_new ();
void                perlin_hermitian_del (perlin_hermitian_t *p);
double              perlin_hermitian_noise (perlin_hermitian_t *p, const point3_t *point);

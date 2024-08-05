#pragma once

#include "point.h"

typedef struct perlin_lattice
{
  int     point_count;
  vec3_t *randvec;
  int    *perm_x;
  int    *perm_y;
  int    *perm_z;
} perlin_lattice_t;

perlin_lattice_t *perlin_lattice_new ();
void              perlin_lattice_del (perlin_lattice_t *p);
double            perlin_lattice_noise (perlin_lattice_t *p, const point3_t *point);

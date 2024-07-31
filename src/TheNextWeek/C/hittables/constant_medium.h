#pragma once

#include "hittable.h"

typedef struct volume
{
  hit_type_t  hit_type; // VOLUME
  hit_fn_t    hit;
  aabb_t      bbox;
  hittable_t *boundary;
  double      neg_inv_density;
} volume_t;

volume_t *constant_medium_new (hittable_t *boundary, double density);

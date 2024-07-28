#pragma once

#include "hittable.h"

typedef struct rotate_y
{
  hit_type_t  hit_type; // ROTATE
  hit_fn_t    hit;
  aabb_t      bbox;
  hittable_t *object;
  double      sin_theta;
  double      cos_theta;
} rotate_y_t;

rotate_y_t *rotate_y_new (hittable_t *object, double angle);

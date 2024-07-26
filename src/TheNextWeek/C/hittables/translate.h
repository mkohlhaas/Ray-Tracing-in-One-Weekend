#pragma once

#include "hittable.h"
#include "vec3.h"

typedef struct translate
{
  hit_type_t  hit_type; // TRANSLATE
  hit_fn_t    hit;
  aabb_t      bbox;
  hittable_t *object;
  vec3_t      offset;
} translate_t;

translate_t *translate_new (hittable_t *object, vec3_t offset);

#pragma once

#include "aabb.h"
#include "material.h"
#include "vec3.h"
#include <stdbool.h>

// `sphere_t` is a `hittable_t`
typedef struct sphere
{
  hit_type_t  hit_type; // SPHERE
  hit_fn_t    hit;
  aabb_t      bbox;
  point3_t    center_start;
  vec3_t      center_vec;
  double      radius;
  material_t *mat;
} sphere_t;

struct hit_record;
struct ray;
sphere_t *sphere_new (point3_t center_start, point3_t center_end, double radius, material_t *mat);
void      sphere_print (sphere_t *s, int indent_lvl);

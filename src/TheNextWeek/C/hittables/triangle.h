#pragma once

// A triangle is just a quad with a different is_interior function.

#include "materials/material.h"

// `triangle_t` is a `hittable_t`
typedef struct triangle
{
  hit_type_t  hit_type; // TRIANGLE
  hit_fn_t    hit;
  aabb_t      bbox;
  point3_t    Q;
  vec3_t      u;
  vec3_t      v;
  vec3_t      w;
  vec3_t      unit_normal;
  double      D;
  material_t *mat;
} triangle_t;

triangle_t *triangle_new (point3_t const Q, vec3_t const u, vec3_t const v, material_t *mat);
void        triangle_print (triangle_t *t, int indent_lvl);

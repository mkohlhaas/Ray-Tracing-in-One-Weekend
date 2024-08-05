#pragma once

#include "material.h"

// `quad_t` is a `hittable_t`
typedef struct quadrilateral
{
  hit_type_t  hit_type; // QUAD
  hit_fn_t    hit;
  aabb_t      bbox;
  point3_t    Q;
  vec3_t      u;
  vec3_t      v;
  vec3_t      w;
  vec3_t      unit_normal;
  double      D;
  material_t *mat;
} quadrilateral_t;

quadrilateral_t *quad_new (point3_t const Q, vec3_t const u, vec3_t const v, material_t *mat);
void             quad_print (quadrilateral_t *q, int indent_lvl);

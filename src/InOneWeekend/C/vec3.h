#pragma once

#include <stdbool.h>

typedef union vec3
{
  double element[3];
  struct
  {
    union
    {
      double x, r, s, u;
    };
    union
    {
      double y, g, t, v;
    };
    union
    {
      double z, b, p, w;
    };
  };
} vec3_t;

bool   vec3_near_zero (vec3_t v);
double vec3_dot (vec3_t v1, vec3_t v2);
double vec3_length (vec3_t v);
double vec3_length_squared (vec3_t v);
vec3_t vec3_add (vec3_t v1, vec3_t v2);
vec3_t vec3_cross (vec3_t v1, vec3_t v2);
vec3_t vec3_uminus (vec3_t v);
vec3_t vec3_mulv (vec3_t v1, vec3_t v2);
vec3_t vec3_random (void);
vec3_t vec3_random_in_unit_disk (void);
vec3_t vec3_random_in_unit_sphere (void);
vec3_t vec3_random_min_max (double min, double max);
vec3_t vec3_random_on_hemisphere (vec3_t const normal);
vec3_t vec3_random_unit_vector_in_sphere (void);
vec3_t vec3_reflect (vec3_t const v, vec3_t const n);
vec3_t vec3_refract (const vec3_t uv, const vec3_t n, double etai_over_etat);
vec3_t vec3_divt (vec3_t v, double t);
vec3_t vec3_mult (double t, vec3_t v);
vec3_t vec3_sub (vec3_t v1, vec3_t v2);
vec3_t vec3_unit (vec3_t v);
void   vec3_print (char *name, vec3_t v);

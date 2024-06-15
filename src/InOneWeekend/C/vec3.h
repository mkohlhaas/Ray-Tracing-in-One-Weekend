#pragma once

#include <stdbool.h>

typedef union vec3_union
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
} vec3;

vec3   vec3_minus (vec3 v);
vec3   vec3_add (vec3 v1, vec3 v2);
vec3   vec3_sub (vec3 v1, vec3 v2);
vec3   vec3_mul (vec3 v1, vec3 v2);
vec3   vec3_scalar_mult (vec3 v, double t);
vec3   vec3_scalar_div (vec3 v, double t);
double vec3_dot_product (vec3 v1, vec3 v2);
vec3   vec3_cross_product (vec3 v1, vec3 v2);
double vec3_length_squared (vec3 v);
double vec3_length (vec3 v);
vec3   vec3_unit (vec3 v);
void   vec3_print (char *name, vec3 v);
vec3   vec3_random (void);
vec3   vec3_random_min_max (double min, double max);
vec3   vec3_random_in_unit_sphere (void);
vec3   vec3_random_unit_vector (void);
vec3   vec3_random_on_hemisphere (vec3 const normal);
bool   vec3_near_zero (vec3 v);
vec3   vec3_reflect (vec3 const v, vec3 const n);
vec3   vec3_random_in_unit_disk (void);

#include "vec3.h"
#include "utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

vec3
vec3_minus (vec3 v)
{
  return (vec3){
    .x = -v.x,
    .y = -v.y,
    .z = -v.z,
  };
}

vec3
vec3_add (vec3 v1, vec3 v2)
{
  return (vec3){
    .x = v1.x + v2.x,
    .y = v1.y + v2.y,
    .z = v1.z + v2.z,
  };
}

vec3
vec3_sub (vec3 v1, vec3 v2)
{
  return (vec3){
    .x = v1.x - v2.x,
    .y = v1.y - v2.y,
    .z = v1.z - v2.z,
  };
}

vec3
vec3_mul (vec3 v1, vec3 v2)
{
  return (vec3){
    .x = v1.x * v2.x,
    .y = v1.y * v2.y,
    .z = v1.z * v2.z,
  };
}

vec3
vec3_scalar_mult (vec3 v, double t)
{
  return (vec3){
    .x = t * v.x,
    .y = t * v.y,
    .z = t * v.z,
  };
}

vec3
vec3_scalar_div (vec3 v, double t)
{
  return vec3_scalar_mult (v, 1 / t);
}

double
vec3_dot_product (vec3 v1, vec3 v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3
vec3_cross_product (vec3 v1, vec3 v2)
{
  return (vec3){
    .x = v1.y * v2.z - v1.z * v2.y,
    .y = v1.z * v2.x - v1.x * v2.z,
    .z = v1.x * v2.y - v1.y * v2.x,
  };
}

double
vec3_length_squared (vec3 v)
{
  return vec3_dot_product (v, v);
}

double
vec3_length (vec3 v)
{
  return sqrt (vec3_length_squared (v));
}

// Returns unit vector of `v`.
vec3
vec3_unit (vec3 v)
{
  return vec3_scalar_div (v, vec3_length (v));
}

void
vec3_print (char *name, vec3 v)
{
  fprintf (stderr, "Vector \"%s\": %f %f %f\n", name, v.x, v.y, v.z);
}

vec3
vec3_random (void)
{
  return (vec3){
    .x = random_double (),
    .y = random_double (),
    .z = random_double (),
  };
}

vec3
vec3_random_min_max (double min, double max)
{
  return (vec3){
    .x = random_double_min_max (min, max),
    .y = random_double_min_max (min, max),
    .z = random_double_min_max (min, max),
  };
}

vec3
vec3_random_in_unit_sphere (void)
{
  while (true)
    {
      vec3 p = vec3_random_min_max (-1, 1);
      if (vec3_length_squared (p) < 1)
        {
          return p;
        }
    }
}

vec3
vec3_random_unit_vector (void)
{
  return vec3_unit (vec3_random_in_unit_sphere ());
}

vec3
vec3_random_on_hemisphere (vec3 const normal)
{
  vec3 on_unit_sphere = vec3_random_unit_vector ();
  if (vec3_dot_product (on_unit_sphere, normal) > 0.0) // in the same hemisphere as the normal
    {
      return on_unit_sphere;
    }
  else
    {
      return vec3_minus (on_unit_sphere);
    }
}

// Return true if the vector is close to zero in all dimensions.
bool
vec3_near_zero (vec3 v)
{
  double s = 1e-8;
  return fabs (v.x) < s && fabs (v.y) < s && fabs (v.z) < s;
}

vec3
vec3_reflect (vec3 const v, vec3 const n)
{
  return vec3_sub (v, vec3_scalar_mult (n, 2 * vec3_dot_product (v, n)));
}

vec3
refract (const vec3 uv, const vec3 n, double etai_over_etat)
{
  auto cos_theta      = fmin (vec3_dot_product (vec3_minus (uv), n), 1.0);
  vec3 r_out_perp     = vec3_scalar_mult (vec3_add (uv, vec3_scalar_mult (n, cos_theta)), etai_over_etat);
  vec3 r_out_parallel = vec3_scalar_mult (n, -sqrt (fabs (1.0 - vec3_length_squared (r_out_perp))));
  return vec3_add (r_out_perp, r_out_parallel);
}

vec3
vec3_random_in_unit_disk (void)
{
  while (true)
    {
      auto p = (vec3){ .x = random_double_min_max (-1.0, 1.0), .y = random_double_min_max (-1, 1), .z = 0 };
      if (vec3_length_squared (p) < 1.0)
        {
          return p;
        }
    }
}

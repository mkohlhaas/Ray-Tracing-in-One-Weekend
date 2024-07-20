#include "math/vec3.h"
#include "utils/utils.h"
#include <math.h>
#include <stdio.h>

// Invert direction of vector `v` (unary minus).
vec3_t
vec3_uminus (vec3_t v)
{
  return (vec3_t){
    .x = -v.x,
    .y = -v.y,
    .z = -v.z,
  };
}

vec3_t
vec3_add (vec3_t v1, vec3_t v2)
{
  return (vec3_t){
    .x = v1.x + v2.x,
    .y = v1.y + v2.y,
    .z = v1.z + v2.z,
  };
}

vec3_t
vec3_sub (vec3_t v1, vec3_t v2)
{
  return (vec3_t){
    .x = v1.x - v2.x,
    .y = v1.y - v2.y,
    .z = v1.z - v2.z,
  };
}

// Vector multiplication.
vec3_t
vec3_mulv (vec3_t v1, vec3_t v2)
{
  return (vec3_t){
    .x = v1.x * v2.x,
    .y = v1.y * v2.y,
    .z = v1.z * v2.z,
  };
}

// Scalar vector multiplication.
vec3_t
vec3_mult (double t, vec3_t v)
{
  return (vec3_t){
    .x = t * v.x,
    .y = t * v.y,
    .z = t * v.z,
  };
}

// Scalar vector division.
vec3_t
vec3_divt (vec3_t v, double t)
{
  return vec3_mult (1 / t, v);
}

double
vec3_dot (vec3_t v1, vec3_t v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3_t
vec3_cross (vec3_t v1, vec3_t v2)
{
  return (vec3_t){
    .x = v1.y * v2.z - v1.z * v2.y,
    .y = v1.z * v2.x - v1.x * v2.z,
    .z = v1.x * v2.y - v1.y * v2.x,
  };
}

double
vec3_length_squared (vec3_t v)
{
  return vec3_dot (v, v);
}

double
vec3_length (vec3_t v)
{
  return sqrt (vec3_length_squared (v));
}

// Returns unit vector of `v`.
vec3_t
vec3_unit (vec3_t v)
{
  return vec3_divt (v, vec3_length (v));
}

void
vec3_print (char *name, vec3_t v)
{
  fprintf (stderr, "Vector \"%s\": %f %f %f\n", name, v.x, v.y, v.z);
}

vec3_t
vec3_random (void)
{
  return (vec3_t){
    .x = random_double (),
    .y = random_double (),
    .z = random_double (),
  };
}

vec3_t
vec3_random_min_max (double min, double max)
{
  return (vec3_t){
    .x = random_double_min_max (min, max),
    .y = random_double_min_max (min, max),
    .z = random_double_min_max (min, max),
  };
}

// Random vector in unit sphere.
vec3_t
vec3_random_in_unit_sphere (void)
{
  while (true)
    {
      vec3_t p = vec3_random_min_max (-1, 1);
      if (vec3_length_squared (p) < 1)
        {
          return p;
        }
    }
}

// Random vector in unit circle.
vec3_t
vec3_random_in_unit_disk (void)
{
  while (true)
    {
      auto x_rnd = random_double_min_max (-1, 1);
      auto y_rnd = random_double_min_max (-1, 1);
      auto p     = (vec3_t){ .x = x_rnd, .y = y_rnd, .z = 0 };
      if (vec3_length_squared (p) < 1.0)
        {
          return p;
        }
    }
}

vec3_t
vec3_random_unit_vector_in_sphere (void)
{
  return vec3_unit (vec3_random_in_unit_sphere ());
}

vec3_t
vec3_random_on_hemisphere (vec3_t const normal)
{
  vec3_t on_unit_sphere = vec3_random_unit_vector_in_sphere ();
  if (vec3_dot (on_unit_sphere, normal) > 0.0) // in the same hemisphere as the normal
    {
      return on_unit_sphere;
    }
  else
    {
      return vec3_uminus (on_unit_sphere);
    }
}

// Returns `true` if the vector is close to zero in all dimensions.
bool
vec3_near_zero (vec3_t v)
{
  double const s = 1e-8;
  return fabs (v.x) < s && fabs (v.y) < s && fabs (v.z) < s;
}

// Returns reflected vector `v` at `n`.
vec3_t
vec3_reflect (vec3_t const v, vec3_t const n)
{
  return vec3_sub (v, vec3_mult (2 * vec3_dot (v, n), n));
}

vec3_t
vec3_refract (const vec3_t uv, const vec3_t n, double etai_over_etat)
{
  auto cos_theta      = fmin (vec3_dot (vec3_uminus (uv), n), 1.0);
  auto r_out_perp     = vec3_mult (etai_over_etat, vec3_add (uv, vec3_mult (cos_theta, n)));
  auto r_out_parallel = vec3_mult (-sqrt (fabs (1.0 - vec3_length_squared (r_out_perp))), n);
  return vec3_add (r_out_perp, r_out_parallel);
}

#include "vec3.h"
#include <math.h>
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

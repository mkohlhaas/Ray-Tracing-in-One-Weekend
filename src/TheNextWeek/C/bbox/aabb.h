#pragma once

#include "interval.h"
#include "point.h"
#include "vec3.h"

typedef enum axis
{
  X_Axis,
  Y_Axis,
  Z_Axis,
  MAX_AXIS,
} axis_t;

typedef union aabb
{
  interval_t element[3];
  struct
  {
    interval_t x_intvl;
    interval_t y_intvl;
    interval_t z_intvl;
  };
} aabb_t;

extern aabb_t const aabb_empty;
extern aabb_t const aabb_universe;

typedef struct ray ray_t;

bool       aabb_hit (aabb_t *bbox, ray_t const *ray, interval_t intvl);
aabb_t     aabb_new_empty ();
aabb_t     aabb_from_aabbs (aabb_t const *bbox0, aabb_t const *bbox1);
aabb_t     aabb_from_intervals (interval_t *x_intvl, interval_t *y_intvl, interval_t *z_intvl);
aabb_t     aabb_from_points (point3_t *p1, point3_t *p2);
interval_t aabb_axis_interval (aabb_t const *bbox, axis_t n);
int        aabb_longest_axis (aabb_t const *bbox);
aabb_t     aabb_add_offset (aabb_t const bbox, vec3_t const offset);

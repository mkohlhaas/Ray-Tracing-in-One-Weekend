#pragma once

#include "interval.h"
#include "point.h"

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

aabb_t    *aabb_new_empty ();
aabb_t    *aabb_from_intervals (interval_t x_intvl, interval_t y_intvl, interval_t z_intvl);
aabb_t    *aabb_from_points (point3_t p1, point3_t p2);
interval_t aabb_axis_interval (aabb_t *bbox, int n);
aabb_t    *aabb_from_aabbs (aabb_t const *bbox0, aabb_t const *bbox1);

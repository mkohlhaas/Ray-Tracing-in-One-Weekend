#include "aabb.h"
#include "error.h"
#include "interval.h"
#include "point.h"
#include "ray.h"

// Returns `true` if `ray` hits `bbox`.
bool
aabb_hit (aabb_t *bbox, ray_t const *ray, interval_t intvl)
{
  for (int axis = 0; axis < 3; axis++)
    {
      auto axis_intvl = aabb_axis_interval (bbox, axis);
      auto adinv      = 1.0 / ray->direction.element[axis];                   // axis direction reciprocal
      auto t0         = (axis_intvl.low - ray->origin.element[axis]) * adinv; // see "The Next Week" p. 9
      auto t1         = (axis_intvl.high - ray->origin.element[axis]) * adinv;

      if (t0 < t1)                                                            // see "The Next Week" p. 11
        {
          if (t0 > intvl.low)
            {
              intvl.low = t0;
            }
          if (t1 < intvl.high)
            {
              intvl.high = t1;
            }
        }
      else // same as above but `t0` and `t1` exchanged
        {
          if (t1 > intvl.low)
            {
              intvl.low = t1;
            }
          if (t0 < intvl.high)
            {
              intvl.high = t0;
            }
        }

      if (intvl.high <= intvl.low)
        {
          return false;
        }
    }
  return true;
}

// New empty `aabb_t`.
// Returns `NULL` if memory allocation failed.
aabb_t *
aabb_new_empty ()
{
  aabb_t *bbox = malloc (sizeof *bbox);
  if (bbox)
    {
      bbox->x_intvl = intvl_empty;
      bbox->y_intvl = intvl_empty;
      bbox->z_intvl = intvl_empty;
    }
  return bbox;
}

// New `aabb_t` from intervals.
// Returns `NULL` if memory allocation failed.
aabb_t *
aabb_from_intervals (interval_t *x_intvl, interval_t *y_intvl, interval_t *z_intvl)
{
  aabb_t *bbox = malloc (sizeof *bbox);
  if (bbox)
    {
      bbox->x_intvl = *x_intvl;
      bbox->y_intvl = *y_intvl;
      bbox->z_intvl = *z_intvl;
    }
  return bbox;
}

// Treat the two points `p1` and `p2` as extrema for the bounding box,
// so we don't require a particular minimum/maximum coordinate order.
// Returns `NULL` if memory allocation failed.
aabb_t *
aabb_from_points (point3_t *p1, point3_t *p2)
{
  auto x = (p1->x <= p2->x) ? (interval_t){ p1->x, p2->x } : (interval_t){ p2->x, p1->x };
  auto y = (p1->y <= p2->y) ? (interval_t){ p1->y, p2->y } : (interval_t){ p2->y, p1->y };
  auto z = (p1->z <= p2->z) ? (interval_t){ p1->z, p2->z } : (interval_t){ p2->z, p1->z };

  aabb_t *bbox = malloc (sizeof *bbox);
  if (bbox)
    {
      bbox->x_intvl = x;
      bbox->y_intvl = y;
      bbox->z_intvl = z;
    }
  return bbox;
}

aabb_t *
aabb_from_aabbs (aabb_t const *bbox0, aabb_t const *bbox1)
{
  aabb_t *bbox = malloc (sizeof *bbox);
  if (bbox)
    {
      bbox->x_intvl = intvl_from_intvls (bbox0->x_intvl, bbox1->x_intvl);
      bbox->y_intvl = intvl_from_intvls (bbox0->y_intvl, bbox1->y_intvl);
      bbox->z_intvl = intvl_from_intvls (bbox0->z_intvl, bbox1->z_intvl);
    }
  return bbox;
}

// Returns interval for specified axis.
// x-axis => `n`=0, y-axis => `n`=1, z-axis => `n`=2.
interval_t
aabb_axis_interval (aabb_t *bbox, int n)
{
  switch (n)
    {
    case 0:
      return bbox->x_intvl;
    case 1:
      return bbox->y_intvl;
    case 2:
      return bbox->z_intvl;
    default:
      logExit ("Should never happen!");
    }
}

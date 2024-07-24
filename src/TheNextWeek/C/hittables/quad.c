#include "hittables/quad.h"
#include "bbox/aabb.h"
#include "hittables/hittable.h"
#include "math/interval.h"
#include "math/vec3.h"
#include <math.h>
#include <stdlib.h>

// Compute the bounding box of all four vertices.
static void
set_bounding_box (quadrilateral_t *q)
{
  auto diag1          = vec3_add (vec3_add (q->Q, q->u), q->v);
  auto q_u            = vec3_add (q->Q, q->u);
  auto q_v            = vec3_add (q->Q, q->v);
  auto bbox_diagonal1 = aabb_from_points (&q->Q, &diag1);
  auto bbox_diagonal2 = aabb_from_points (&q_u, &q_v);
  q->bbox             = aabb_from_aabbs (&bbox_diagonal1, &bbox_diagonal2);
}

static bool
is_interior (double a, double b)
{
  auto unit_interval = (interval_t){ .low = 0, .high = 1 };

  if (intvl_contains (unit_interval, a) && intvl_contains (unit_interval, b))
    {
      return true; // a, b are in unit interval
    }
  else
    {
      return false;
    }
}

static bool
quad_hit (ray_t const ray, hittable_t *object, interval_t intvl, hit_record_t *rec)
{
  quadrilateral_t *q = (quadrilateral_t *)object;

  auto denom = vec3_dot (q->unit_normal, ray.direction);

  // No hit if the ray is parallel to the plane.
  if (fabs (denom) < 1e-8)
    {
      return false;
    }

  // Return false if the hit point parameter t is outside the ray interval.
  auto t = (q->D - vec3_dot (q->unit_normal, ray.origin)) / denom;
  if (!intvl_contains (intvl, t))
    {
      return false;
    }

  // Determine the hit point lies within the planar shape using its plane coordinates.
  auto P     = point_at (ray, t);
  auto p     = vec3_sub (P, q->Q);
  auto alpha = vec3_dot (q->w, vec3_cross (p, q->v));
  auto beta  = vec3_dot (q->w, vec3_cross (q->u, p));

  if (!is_interior (alpha, beta))
    {
      return false;
    }

  // Ray hits the 2D shape; set the rest of the hit record and return true.
  rec->object = object;
  rec->p      = P;
  rec->t      = t;
  rec->u      = alpha;
  rec->v      = beta;
  set_face_normal (rec, ray, q->unit_normal);

  return true;
}

quadrilateral_t *
quad_new (point3_t const Q, vec3_t const u, vec3_t const v, material_t *mat)
{
  quadrilateral_t *q = malloc (sizeof *q);
  if (q)
    {
      q->hit_type = QUAD;
      q->hit      = quad_hit;
      q->Q        = Q;
      q->u        = u;
      q->v        = v;
      q->mat      = mat;

      auto n         = vec3_cross (u, v);
      q->unit_normal = vec3_unit (n);
      q->D           = vec3_dot (q->unit_normal, Q);
      q->w           = vec3_divt (n, vec3_dot (n, n));

      set_bounding_box (q);
    }
  return q;
}

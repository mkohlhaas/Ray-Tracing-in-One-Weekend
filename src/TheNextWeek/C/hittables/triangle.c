#include "hittables/triangle.h"
#include "bbox/aabb.h"
#include "hittables/hittable.h"
#include "math/interval.h"
#include "math/vec3.h"
#include <math.h>
#include <stdlib.h>

// Compute the bounding box of all four vertices.
static void
set_bounding_box (triangle_t *q)
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
  if ((a < 0) || (b < 0) || (a + b > 1))
    {
      return false;
    }
  else
    {
      return true;
    }
}

static bool
triangle_hit (ray_t const ray, hittable_t *object, interval_t intvl, hit_record_t *rec)
{
  triangle_t *tri = (triangle_t *)object;

  auto denom = vec3_dot (tri->unit_normal, ray.direction);

  // No hit if the ray is parallel to the plane.
  if (fabs (denom) < 1e-8)
    {
      return false;
    }

  // Return false if the hit point parameter t is outside the ray interval.
  auto t = (tri->D - vec3_dot (tri->unit_normal, ray.origin)) / denom;
  if (!intvl_contains (intvl, t))
    {
      return false;
    }

  // Determine the hit point lies within the planar shape using its plane coordinates.
  auto P     = point_at (ray, t);
  auto p     = vec3_sub (P, tri->Q);
  auto alpha = vec3_dot (tri->w, vec3_cross (p, tri->v));
  auto beta  = vec3_dot (tri->w, vec3_cross (tri->u, p));

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
  set_face_normal (rec, ray, tri->unit_normal);

  return true;
}

triangle_t *
triangle_new (point3_t const Q, vec3_t const u, vec3_t const v, material_t *mat)
{
  triangle_t *q = malloc (sizeof *q);
  if (q)
    {
      q->hit_type = TRIANGLE;
      q->hit      = triangle_hit;
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

void
triangle_print (triangle_t *t, int indent_lvl)
{
  fprintf (stderr, "%*sTriangle (%f %f) (%f %f) (%f %f)\n", indent_lvl, "", t->bbox.x_intvl.low, t->bbox.x_intvl.high,
           t->bbox.y_intvl.low, t->bbox.y_intvl.high, t->bbox.z_intvl.low, t->bbox.z_intvl.high);
}

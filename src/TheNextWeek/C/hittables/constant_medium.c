#include "constant_medium.h"
#include "aabb.h"
#include "error.h"
#include "globals.h"
#include "hittable.h"
#include "interval.h"
#include "isotropic.h"
#include "material.h"
#include "ray.h"
#include "texture.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

bool
constant_medium_hit (ray_t const ray, hittable_t *object, interval_t intvl, hit_record_t *rec)
{
  volume_t *v = (volume_t *)object;

  // Print occasional samples when debugging. To enable, set enableDebug true.
  const bool debugging = g_enableDebug && random_double () < 0.00001;

  hit_record_t rec1, rec2;

  if (!v->boundary->hit (ray, v->boundary, intvl_universe, &rec1))
    {
      return false;
    }

  if (!v->boundary->hit (ray, v->boundary, (interval_t){ rec1.t + 0.0001, INFINITY }, &rec2))
    {
      return false;
    }

  if (debugging)
    {
      fprintf (stderr, "t_min = %f, t_max = %f\n", rec1.t, rec2.t);
    }

  if (rec1.t < intvl.low)
    {
      rec1.t = intvl.low;
    }
  if (rec2.t > intvl.high)
    {
      rec2.t = intvl.high;
    }

  if (rec1.t >= rec2.t)
    {
      return false;
    }

  if (rec1.t < 0)
    {
      rec1.t = 0;
    }

  auto ray_length               = vec3_length (ray.direction);
  auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
  auto hit_distance             = v->neg_inv_density * log (random_double ());

  if (hit_distance > distance_inside_boundary)
    {
      return false;
    }

  rec->t = rec1.t + hit_distance / ray_length;
  rec->p = point_at (ray, rec->t);

  if (debugging)
    {
      fprintf (stderr, "hit_distance = %f\n", hit_distance);
      fprintf (stderr, "rec.t = %f", rec->t);
      fprintf (stderr, "rec.p = (%f %f %f)\n", rec->p.x, rec->p.y, rec->p.z);
    }

  rec->unit_normal = (vec3_t){ .x = 1, .y = 0, .z = 0 }; // arbitrary
  rec->front_face  = true;                               // also arbitrary
  rec->object      = rec1.object;

  return true;
}

volume_t *
constant_medium_new (hittable_t *boundary, double density)
{
  volume_t *cm = malloc (sizeof *cm);
  if (!cm)
    {
      logExit ("Out of memory");
    }
  cm->hit_type        = VOLUME;
  cm->hit             = constant_medium_hit;
  cm->bbox            = boundary->bbox;
  cm->boundary        = boundary;
  cm->neg_inv_density = -1.0 / density;
  // cm->phase_function  = (material_t *)isotropic_from_color (albedo);
  return cm;
}

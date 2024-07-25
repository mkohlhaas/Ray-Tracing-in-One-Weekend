#include "materials/material.h"
#include "error/error.h"
#include "hittable.h"
#include "hittables/quad.h"
#include "hittables/sphere.h"
#include "hittables/triangle.h"

material_t *
get_material (hittable_t *object)
{
  switch (object->hit_type)
    {
    case SPHERE:
      sphere_t *s = (sphere_t *)object;
      return s->mat;
      break;
    case QUAD:
      quadrilateral_t *q = (quadrilateral_t *)object;
      return q->mat;
      break;
    case TRIANGLE:
      triangle_t *t = (triangle_t *)object;
      return t->mat;
      break;
    default:
      logExit ("Should never happen");
    }
}

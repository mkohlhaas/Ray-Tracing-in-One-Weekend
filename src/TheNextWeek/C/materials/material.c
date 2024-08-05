#include "material.h"
#include "error.h"
#include "hittable.h"
#include "quad.h"
#include "sphere.h"
#include "triangle.h"

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

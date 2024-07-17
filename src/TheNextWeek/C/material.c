#include "material.h"
#include "error.h"
#include "sphere.h"

material_t *
get_material (hittable_t *object)
{
  switch (object->hit_type)
    {
    case SPHERE:
      sphere_t *s = (sphere_t *)object;
      return s->mat;
      break;
    default:
      logExit ("Should never happen");
    }
}

#include "material.h"
#include "error.h"
#include "sphere.h"
#include <stdlib.h>

material_t *
get_material (hittable_t *object)
{
  switch (object->hit_type)
    {
    case SPHERE:
      sphere_t *s = (sphere_t *)object;
      return s->mat;
      break;
    case HITTABLE_LIST:
      logExit ("Should never happen");
      break;
    default:
      logExit ("Should never happen");
    }
  return NULL; // just to make compiler happy
}

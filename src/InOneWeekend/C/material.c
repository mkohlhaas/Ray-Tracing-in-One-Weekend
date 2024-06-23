#include "material.h"
#include "sphere.h"
#include <stdlib.h>

material_t *
get_material (hit_able_t *object)
{
  switch (object->type)
    {
    case SPHERE:
      sphere_t *s = (sphere_t *)object;
      return s->mat;
      break;
    case LIST:
      exit (EXIT_FAILURE); // should never happen
      break;
    default:
      exit (EXIT_FAILURE); // should never happen
    }
  return NULL;             // just to make compiler happy
}

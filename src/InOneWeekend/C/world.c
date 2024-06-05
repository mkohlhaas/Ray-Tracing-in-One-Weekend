#include "hittable.h"
#include "sphere.h"
#include "stb_ds.h"

hittable **world = NULL;

void
world_init (void)
{
  sphere *s1 = sphere_new (
      (point3){
          .x = 0,
          .y = 0,
          .z = -1,
      },
      0.5);
  hittable *sh1 = hittable_new (hit_sphere, s1);
  arrput (world, sh1);

  sphere *s2 = sphere_new (
      (point3){
          .x = 0,
          .y = -100.5,
          .z = -1,
      },
      100);
  hittable *sh2 = hittable_new (hit_sphere, s2);
  arrput (world, sh2);
}

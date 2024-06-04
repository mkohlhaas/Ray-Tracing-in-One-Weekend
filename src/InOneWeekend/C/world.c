#include "hittable.h"
#include "sphere.h"

GArray *world;

void
world_init (void)
{
  world = g_array_new (FALSE, FALSE, sizeof (hittable *));

  sphere   *s1  = sphere_new ((point3){ .x = 0, .y = 0, .z = -1 }, 0.5);
  hittable *sh1 = hittable_new (hit_sphere, s1);
  g_array_append_val (world, sh1);
  // sphere    S1  = { (point3){ .x = 0, .y = 0, .z = -1 }, 0.5 };
  // hittable  SH1 = { hit_sphere, &S1 };

  sphere   *s2  = sphere_new ((point3){ .x = 0, .y = -100.5, .z = -1 }, 100);
  hittable *sh2 = hittable_new (hit_sphere, s2);
  g_array_append_val (world, sh2);

  // sphere   S2  = { (point3){ .x = 0, .y = -100.5, .z = -1 }, 100 };
  // hittable SH2 = { hit_sphere, &S2 };
  // g_array_append_val (world, SH2);
}

#include "color.h"
#include "dielectric.h"
#include "hittable.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"
#include "stb_ds.h"

hittable **world = NULL;

void
world_init (void)
{
  auto material_ground = lambertian_new ((color){ .r = 0.8, .g = 0.8, .b = 0.0 });
  auto material_center = lambertian_new ((color){ .r = 0.1, .g = 0.2, .b = 0.5 });
  auto material_left   = dielectric_new (1.50);
  auto material_bubble = dielectric_new (1.00 / 1.50);
  auto material_right  = metal_new ((color){ .r = 0.8, .g = 0.6, .b = 0.2 }, 1.0);

  sphere *s1 = sphere_new ((point3){ .x = 0.0, .y = -100.5, .z = -1.0 }, 100.0, (material *)material_ground);
  sphere *s2 = sphere_new ((point3){ .x = 0.0, .y = 0.0, .z = -1.2 }, 0.5, (material *)material_center);
  sphere *s3 = sphere_new ((point3){ .x = -1.0, .y = 0.0, .z = -1.0 }, 0.5, (material *)material_left);
  sphere *s4 = sphere_new ((point3){ .x = -1.0, .y = 0.0, .z = -1.0 }, 0.4, (material *)material_bubble);
  sphere *s5 = sphere_new ((point3){ .x = 1.0, .y = 0.0, .z = -1.0 }, 0.5, (material *)material_right);

  // TOOD: write hittable_sphere
  hittable *sh1 = hittable_new (sphere_hit, s1);
  hittable *sh2 = hittable_new (sphere_hit, s2);
  hittable *sh3 = hittable_new (sphere_hit, s3);
  hittable *sh4 = hittable_new (sphere_hit, s4);
  hittable *sh5 = hittable_new (sphere_hit, s5);

  arrput (world, sh1);
  arrput (world, sh2);
  arrput (world, sh3);
  arrput (world, sh4);
  arrput (world, sh5);
}

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

  lambertian *material_ground = lambertian_new ((color){ .r = 0.8, .g = 0.8, .b = 0.0 });
  lambertian *material_center = lambertian_new ((color){ .r = 0.1, .g = 0.2, .b = 0.5 });
  dielectric *material_left   = dielectric_new (1.5);
  metal      *material_right  = metal_new ((color){ .r = 0.8, .g = 0.6, .b = 0.2 }, 1.0);

  sphere *s1 = sphere_new (
      (point3){
          .x = 0.0,
          .y = -100.5,
          .z = -1.0,
      },
      100.0, (material *)material_ground);
  hittable *sh1 = hittable_new (sphere_hit, s1);
  arrput (world, sh1);

  sphere *s2 = sphere_new (
      (point3){
          .x = 0.0,
          .y = 0.0,
          .z = -1.2,
      },
      0.5, (material *)material_center);
  hittable *sh2 = hittable_new (sphere_hit, s2);
  arrput (world, sh2);

  sphere *s3 = sphere_new (
      (point3){
          .x = -1.0,
          .y = 0.0,
          .z = -1.0,
      },
      0.5, (material *)material_left);
  hittable *sh3 = hittable_new (sphere_hit, s3);
  arrput (world, sh3);

  sphere *s4 = sphere_new (
      (point3){
          .x = 1.0,
          .y = 0.0,
          .z = -1.0,
      },
      0.5, (material *)material_right);
  hittable *sh4 = hittable_new (sphere_hit, s4);
  arrput (world, sh4);
}

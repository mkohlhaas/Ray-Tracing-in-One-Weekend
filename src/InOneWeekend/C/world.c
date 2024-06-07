#include "color.h"
#include "dielectric.h"
#include "hittable.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"
#include "stb_ds.h"
#include <math.h>

hittable **world = NULL;

void
world_init (void)
{
  auto material_left  = lambertian_new (blue);
  auto material_right = lambertian_new (red);

  auto R = cos (M_PI / 4);

  sphere *s1 = sphere_new (
      (point3){
          .x = -R,
          .y = 0,
          .z = -1,
      },
      R, (material *)material_left);
  hittable *sh1 = hittable_new (sphere_hit, s1);
  arrput (world, sh1);

  sphere *s2 = sphere_new (
      (point3){
          .x = R,
          .y = 0,
          .z = -1,
      },
      R, (material *)material_right);
  hittable *sh2 = hittable_new (sphere_hit, s2);
  arrput (world, sh2);
}

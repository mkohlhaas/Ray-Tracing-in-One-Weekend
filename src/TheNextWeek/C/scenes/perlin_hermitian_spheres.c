#include "hittable_list.h"
#include "lambertian.h"
#include "noise_hermitian.h"
#include "scenes.h"
#include "sphere.h"
#include "world.h"

void
perlin_hermitian_spheres ()
{
  // ground
  auto center = (point3_t){ .x = 0.0, .y = -1000.0, .z = 0.0 };
  auto tex    = noise_hermitian_texture_new ();
  auto m      = lambertian_new_with_tex ((texture_t *)tex);
  auto s      = sphere_new (center, center, 1000, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // sphere
  center = (point3_t){ .x = 3.0, .y = 3.0, .z = -4.0 };
  tex    = noise_hermitian_texture_new ();
  m      = lambertian_new_with_tex ((texture_t *)tex);
  s      = sphere_new (center, center, 3, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);
}

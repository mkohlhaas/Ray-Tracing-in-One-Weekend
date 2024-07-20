#include "hittables/hittable_list.h"
#include "hittables/sphere.h"
#include "materials/lambertian.h"
#include "scenes/scenes.h"
#include "textures/noise_phase.h"
#include "world/world.h"

void
perlin_phase_spheres ()
{
  // ground
  auto center = (point3_t){ .x = 0.0, .y = -1000.0, .z = 0.0 };
  auto tex    = noise_phase_texture_new (1.8);
  auto m      = lambertian_new_with_tex ((texture_t *)tex);
  auto s      = sphere_new (center, center, 1000, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // sphere #1
  center = (point3_t){ .x = 3.0, .y = 3.0, .z = -4.0 };
  tex    = noise_phase_texture_new (1.2);
  m      = lambertian_new_with_tex ((texture_t *)tex);
  s      = sphere_new (center, center, 3, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // sphere #2
  center = (point3_t){ .x = 10.0, .y = 1.5, .z = -4.0 };
  tex    = noise_phase_texture_new (1.5);
  m      = lambertian_new_with_tex ((texture_t *)tex);
  s      = sphere_new (center, center, 1.5, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);
}

#include "scenes/earth.h"
#include "hittables/hittable_list.h"
#include "hittables/sphere.h"
#include "materials/lambertian.h"
#include "scenes/scenes.h"
#include "textures/image_texture.h"
#include "world/world.h"

void
earth ()
{
  auto center = (point3_t){ .x = 0.0, .y = 0.0, .z = 0.0 };
  auto tex    = image_texture_from_file ("earthmap.png");
  auto m      = lambertian_new_with_tex ((texture_t *)tex);
  auto s      = sphere_new (center, center, 2.0, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);
}

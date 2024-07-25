#include "scenes/simple_light.h"
#include "color.h"
#include "diffuse_light.h"
#include "hittables/hittable_list.h"
#include "hittables/sphere.h"
#include "materials/lambertian.h"
#include "noise_phase.h"
#include "point.h"
#include "quad.h"
#include "scenes/scenes.h"
#include "vec3.h"
#include "world/world.h"

void
simple_light ()
{
  auto tex = noise_phase_texture_new (4);

  // huge sphere (plane)
  {
    auto center = (point3_t){ .x = 0, .y = -1000, .z = 0 };
    auto m      = lambertian_new_with_tex ((texture_t *)tex);
    auto s      = sphere_new (center, center, 1000, (mat_t *)m);
    CHECK_MEMORY;
    hittable_list_add (g_world_list, (hittable_t *)s);
  }

  // small sphere
  {
    auto center = (point3_t){ .x = 0, .y = 2, .z = 0 };
    auto m      = lambertian_new_with_tex ((texture_t *)tex);
    auto s      = sphere_new (center, center, 2, (mat_t *)m);
    CHECK_MEMORY;
    hittable_list_add (g_world_list, (hittable_t *)s);
  }

  // diffuse light
  {
    auto col = (color_t){ .r = 4, .g = 4, .b = 4 };
    auto m   = diffuse_light_from_color (col);
    auto Q   = (point3_t){ .x = 3, .y = 1, .z = -2 };
    auto u   = (vec3_t){ .x = 2, .y = 0, .z = 0 };
    auto v   = (vec3_t){ .x = 0, .y = 2, .z = 0 };
    auto s   = quad_new (Q, u, v, (mat_t *)m);
    CHECK_MEMORY;
    hittable_list_add (g_world_list, (hittable_t *)s);

    // sphere light
    {
      auto center = (point3_t){ .x = 0, .y = 7, .z = 0 };
      auto s      = sphere_new (center, center, 2, (mat_t *)m);
      CHECK_MEMORY;
      hittable_list_add (g_world_list, (hittable_t *)s);
    }
  }
}

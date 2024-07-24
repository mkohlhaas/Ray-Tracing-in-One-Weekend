#include "scenes/triangles.h"
#include "hittables/triangle.h"
#include "materials/lambertian.h"
#include "math/color.h"
#include "scenes/scenes.h"
#include "world/world.h"

void
triangles ()
{
  // triangle #1 (reddish)
  auto m = lambertian_new ((color_t){ .r = 1.0, .g = 0.2, .b = 0.2 });
  auto q = (point3_t){ .x = -3, .y = -2, .z = 5 };
  auto u = (vec3_t){ .x = 0, .y = 0, .z = -4 };
  auto v = (vec3_t){ .x = 0, .y = 4, .z = 0 };
  auto s = triangle_new (q, u, v, (material_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // triangle #2 (greenish)
  m = lambertian_new ((color_t){ .r = 0.2, .g = 1.0, .b = 0.2 });
  q = (point3_t){ .x = -2, .y = -2, .z = 0 };
  u = (vec3_t){ .x = 4, .y = 0, .z = 0 };
  v = (vec3_t){ .x = 0, .y = 4, .z = 0 };
  s = triangle_new (q, u, v, (material_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // triangle #3 (blueish)
  m = lambertian_new ((color_t){ .r = 0.2, .g = 0.2, .b = 1.0 });
  q = (point3_t){ .x = 3, .y = -2, .z = 1 };
  u = (vec3_t){ .x = 0, .y = 0, .z = 4 };
  v = (vec3_t){ .x = 0, .y = 4, .z = 0 };
  s = triangle_new (q, u, v, (material_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // triangle #4 (orange)
  m = lambertian_new ((color_t){ .r = 1.0, .g = 0.5, .b = 0.0 });
  q = (point3_t){ .x = -2, .y = 3, .z = 1 };
  u = (vec3_t){ .x = 4, .y = 0, .z = 0 };
  v = (vec3_t){ .x = 0, .y = 0, .z = 4 };
  s = triangle_new (q, u, v, (material_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // triangle #5 (dark green)
  m = lambertian_new ((color_t){ .r = 0.2, .g = 0.8, .b = 0.8 });
  q = (point3_t){ .x = -2, .y = -3, .z = 5 };
  u = (vec3_t){ .x = 4, .y = 0, .z = 0 };
  v = (vec3_t){ .x = 0, .y = 0, .z = -4 };
  s = triangle_new (q, u, v, (material_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);
}

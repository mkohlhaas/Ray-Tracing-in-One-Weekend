#include "cornell_box.h"
#include "color.h"
#include "diffuse_light.h"
#include "hittables/hittable_list.h"
#include "materials/lambertian.h"
#include "point.h"
#include "quad.h"
#include "scenes/scenes.h"
#include "vec3.h"
#include "world/world.h"

void
cornell_box ()
{
  // left wall
  auto green = (color_t){ .r = 0.12, .g = 0.45, .b = 0.15 };
  auto m     = lambertian_new (green);
  auto Q     = (point3_t){ .x = 555, .y = 0, .z = 0 };
  auto u     = (vec3_t){ .x = 0, .y = 555, .z = 0 };
  auto v     = (vec3_t){ .x = 0, .y = 0, .z = 555 };
  auto s     = quad_new (Q, u, v, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // ceiling, middle, floor
  // world.add (make_shared<quad> (point3 (0, 0, 555), vec3 (555, 0, 0), vec3 (0, 555, 0), white));
  auto white = (color_t){ .r = 0.73, .g = 0.73, .b = 0.73 };
  m          = lambertian_new (white);
  Q          = (point3_t){ .x = 0, .y = 0, .z = 0 };
  u          = (vec3_t){ .x = 555, .y = 0, .z = 0 };
  v          = (vec3_t){ .x = 0, .y = 0, .z = 555 };
  s          = quad_new (Q, u, v, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  m = lambertian_new (white);
  Q = (point3_t){ .x = 555, .y = 555, .z = 555 };
  u = (vec3_t){ .x = -555, .y = 0, .z = 0 };
  v = (vec3_t){ .x = 0, .y = 0, .z = -555 };
  s = quad_new (Q, u, v, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  m = lambertian_new (white);
  Q = (point3_t){ .x = 0, .y = 0, .z = 555 };
  u = (vec3_t){ .x = 555, .y = 0, .z = 0 };
  v = (vec3_t){ .x = 0, .y = 555, .z = 0 };
  s = quad_new (Q, u, v, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // right wall
  // world.add (make_shared<quad> (point3 (0, 0, 0), vec3 (0, 555, 0), vec3 (0, 0, 555), red));
  auto red = (color_t){ .r = 0.65, .g = 0.05, .b = 0.05 };
  m        = lambertian_new (red);
  Q        = (point3_t){ .x = 0, .y = 0, .z = 0 };
  u        = (vec3_t){ .x = 0, .y = 555, .z = 0 };
  v        = (vec3_t){ .x = 0, .y = 0, .z = 555 };
  s        = quad_new (Q, u, v, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // diffuse light at ceiling
  auto bright_white = (color_t){ .r = 15, .g = 15, .b = 15 };
  m                 = (lambertian_t *)diffuse_light_from_color (bright_white);
  Q                 = (point3_t){ .x = 343, .y = 554, .z = 332 };
  u                 = (vec3_t){ .x = -130, .y = 0, .z = 0 };
  v                 = (vec3_t){ .x = 0, .y = 0, .z = -105 };
  s                 = quad_new (Q, u, v, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);
}

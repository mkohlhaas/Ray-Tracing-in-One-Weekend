#include "cornell_box_real.h"
#include "color.h"
#include "diffuse_light.h"
#include "hittable_list.h"
#include "lambertian.h"
#include "point.h"
#include "quad.h"
#include "rotate_y.h"
#include "scenes.h"
#include "translate.h"
#include "vec3.h"
#include "world.h"
#include <math.h>

// Returns the 3D box (six sides) that contains the two opposite vertices a & b.
static hittable_list_t *
box (point3_t const *a, point3_t const *b, material_t *mat)
{
  auto sides = hittable_list_new ();

  // Construct the two opposite vertices with the minimum and maximum coordinates.
  auto min = (point3_t){ .x = fmin (a->x, b->x), .y = fmin (a->y, b->y), .z = fmin (a->z, b->z) };
  auto max = (point3_t){ .x = fmax (a->x, b->x), .y = fmax (a->y, b->y), .z = fmax (a->z, b->z) };

  auto dx = (vec3_t){ .x = max.x - min.x, .y = 0, .z = 0 };
  auto dy = (vec3_t){ .x = 0, .y = max.y - min.y, .z = 0 };
  auto dz = (vec3_t){ .x = 0, .y = 0, .z = max.z - min.z };

  auto front  = quad_new ((point3_t){ .x = min.x, .y = min.y, .z = max.z }, dx, dy, mat);
  auto right  = quad_new ((point3_t){ .x = max.x, .y = min.y, .z = max.z }, vec3_uminus (dz), dy, mat);
  auto back   = quad_new ((point3_t){ .x = max.x, .y = min.y, .z = min.z }, vec3_uminus (dx), dy, mat);
  auto left   = quad_new ((point3_t){ .x = min.x, .y = min.y, .z = min.z }, dz, dy, mat);
  auto top    = quad_new ((point3_t){ .x = min.x, .y = max.y, .z = max.z }, dx, vec3_uminus (dz), mat);
  auto bottom = quad_new ((point3_t){ .x = min.x, .y = min.y, .z = min.z }, dx, dz, mat);

  hittable_list_add (sides, (hittable_t *)front);
  hittable_list_add (sides, (hittable_t *)right);
  hittable_list_add (sides, (hittable_t *)back);
  hittable_list_add (sides, (hittable_t *)left);
  hittable_list_add (sides, (hittable_t *)top);
  hittable_list_add (sides, (hittable_t *)bottom);

  return sides;
}

void
cornell_box_real ()
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

  m              = lambertian_new (white);
  mat_t *box_mat = (mat_t *)m;
  Q              = (point3_t){ .x = 0, .y = 0, .z = 555 };
  u              = (vec3_t){ .x = 555, .y = 0, .z = 0 };
  v              = (vec3_t){ .x = 0, .y = 555, .z = 0 };
  s              = quad_new (Q, u, v, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // right wall
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

  // larger box in background
  auto box1   = box (&((point3_t){ .x = 0, .y = 0, .z = 0 }), &((point3_t){ .x = 165, .y = 330, .z = 165 }), box_mat);
  auto box1_r = rotate_y_new ((hittable_t *)box1, 15);
  auto box1_t = translate_new ((hittable_t *)box1_r, (vec3_t){ .x = 265, .y = 0, .z = 295 });
  hittable_list_add (g_world_list, (hittable_t *)box1_t);

  // smaller box in foreground
  auto box2   = box (&((point3_t){ .x = 0, .y = 0, .z = 0 }), &((point3_t){ .x = 165, .y = 165, .z = 165 }), box_mat);
  auto box2_r = rotate_y_new ((hittable_t *)box2, -18);
  auto box2_t = translate_new ((hittable_t *)box2_r, (vec3_t){ .x = 130, .y = 0, .z = 65 });
  hittable_list_add (g_world_list, (hittable_t *)box2_t);
}

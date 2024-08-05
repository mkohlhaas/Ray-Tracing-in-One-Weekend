#include "bvh_node.h"
#include "color.h"
#include "constant_medium.h"
#include "dielectric.h"
#include "diffuse_light.h"
#include "globals.h"
#include "hittable_list.h"
#include "image_texture.h"
#include "lambertian.h"
#include "material.h"
#include "noise_phase.h"
#include "point.h"
#include "quad.h"
#include "sphere.h"
#include "texture.h"
#include "translate.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>

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
final ()
{
  // ground boxes
  auto      boxes1         = hittable_list_new ();
  auto      ground         = lambertian_new ((color_t){ .r = 0.48, .g = 0.83, .b = 0.53 });
  int const boxes_per_side = 20;
  for (int i = 0; i < boxes_per_side; i++)
    {
      for (int j = 0; j < boxes_per_side; j++)
        {
          auto w  = 100.0;
          auto x0 = -1000.0 + i * w;
          auto z0 = -1000.0 + j * w;
          auto y0 = 0.0;
          auto x1 = x0 + w;
          auto y1 = random_double_min_max (1, 101);
          auto z1 = z0 + w;
          hittable_list_add (boxes1, (hittable_t *)box (&((point3_t){ .x = x0, .y = y0, .z = z0 }),
                                                        &((point3_t){ .x = x1, .y = y1, .z = z1 }), (mat_t *)ground));
        }
    }
  auto boxes_bvh = bvh_node_new (boxes1->hittables);
  hittable_list_add (g_world_list, (hittable_t *)boxes_bvh);

  // light
  auto light = diffuse_light_from_color ((color_t){ .r = 7, .g = 7, .b = 7 });
  auto quad1 = quad_new ((point3_t){ .x = 123, .y = 554, .z = 147 }, (vec3_t){ .x = 300, .y = 0, .z = 0 },
                         (vec3_t){ .x = 0, .y = 0, .z = 265 }, (mat_t *)light);
  hittable_list_add (g_world_list, (hittable_t *)quad1);

  // brown moving ball
  // auto center1_start    = (point3_t){ .x = 400, .y = 400, .z = 200 };
  // auto center1_end      = vec3_add (center1_start, (vec3_t){ .x = 30, .y = 0, .z = 0 });
  // auto sphere_material1 = lambertian_new ((color_t){ .r = 0.7, .g = 0.3, .b = 0.1 });
  // auto sphere1          = sphere_new (center1_start, center1_end, 50, (mat_t *)sphere_material1);
  // hittable_list_add (g_world_list, (hittable_t *)sphere1);

  // glass ball
  auto center2 = (point3_t){ .x = 260, .y = 150, .z = 45 };
  auto sphere2 = sphere_new (center2, center2, 50, (mat_t *)dielectric_new (1.5));
  hittable_list_add (g_world_list, (hittable_t *)sphere2);

  // "blue" ball
  auto center3   = (point3_t){ .x = 360, .y = 150, .z = 145 };
  auto boundary1 = sphere_new (center3, center3, 70, (mat_t *)dielectric_new (1.5));
  hittable_list_add (g_world_list, (hittable_t *)boundary1);
  auto cm1 = constant_medium_new ((hittable_t *)boundary1, 0.2); // blue = color (0.2, 0.4, 0.9)
  hittable_list_add (g_world_list, (hittable_t *)cm1);

  // earth
  auto emat    = lambertian_new_with_tex ((texture_t *)image_texture_from_file ("earthmap.jpg"));
  auto center4 = (point3_t){ .x = 400, .y = 200, .z = 400 };
  auto sphere4 = sphere_new (center4, center4, 100, (mat_t *)emat);
  hittable_list_add (g_world_list, (hittable_t *)sphere4);

  // perlin ball
  auto perlin_tex = noise_phase_texture_new (0.2);
  auto center5    = (point3_t){ .x = 220, .y = 280, .z = 300 };
  auto sphere5    = sphere_new (center5, center5, 80, (mat_t *)lambertian_new_with_tex ((texture_t *)perlin_tex));
  hittable_list_add (g_world_list, (hittable_t *)sphere5);

  // ball cloud
  auto      boxes2    = hittable_list_new ();
  auto      lam_white = lambertian_new ((color_t){ .r = .73, .g = .73, .b = .73 });
  int const ns        = 1000;
  for (int j = 0; j < ns; j++)
    {
      auto random_center = vec3_random_min_max (0, 165);
      hittable_list_add (boxes2, (hittable_t *)sphere_new (random_center, random_center, 10, (mat_t *)lam_white));
    }
  auto boxes2_bvh = bvh_node_new (boxes2->hittables);
  // auto boxes2_r   = rotate_y_new ((hittable_t *)boxes2_bvh, 15); // rotate does not work
  auto boxes2_t = translate_new ((hittable_t *)boxes2_bvh, (vec3_t){ .x = -100, .y = 270, .z = 395 });
  hittable_list_add (g_world_list, (hittable_t *)boxes2_t);
}

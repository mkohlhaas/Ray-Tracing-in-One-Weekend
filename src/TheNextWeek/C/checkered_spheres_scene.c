#include "checkered_spheres_scene.h"
#include "checker_texture.h"
#include "hittable_list.h"
#include "lambertian.h"
#include "scenes.h"
#include "sphere.h"
#include "world.h"

void
checkered_spheres ()
{
  auto checker = checker_texture_from_colors (0.32,
                                              &((color_t){
                                                  .r = .2,
                                                  .g = .3,
                                                  .b = .1,
                                              }),
                                              &((color_t){
                                                  .r = .9,
                                                  .g = .9,
                                                  .b = .9,
                                              }));
  auto m       = lambertian_new_with_tex ((texture_t *)checker);

  // sphere #1
  auto c = (point3_t){ .x = 0.0, .y = -10.0, .z = 0.0 };
  auto s = sphere_new (c, c, 10.0, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world_list, (hittable_t *)s);

  // sphere #2
  c = (point3_t){ .x = 0.0, .y = 10.0, .z = 0.0 };
  s = sphere_new (c, c, 10.0, (mat_t *)m);
  hittable_list_add (g_world_list, (hittable_t *)s);
}

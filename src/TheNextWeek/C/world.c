#include "dielectric.h"
#include "error.h"
#include "hittable_list.h"
#include "lambertian.h"
#include "metal.h"
#include "point.h"
#include "sphere.h"
#include "stb_ds.h"
#include "utils.h"
#include "vec3.h"
#include <stdio.h>

// global world
// hittable_t **g_world = NULL;
hittable_list_t *g_world = NULL;

#define CHECK_MEMORY                                                                                                   \
  if (!m || !s)                                                                                                        \
    {                                                                                                                  \
      logExit ("Out of memory");                                                                                       \
    }

// Ground is a just a very huge sphere.
static void
create_ground ()
{
  auto m      = lambertian_new ((color_t){ .r = 0.5, .g = 0.5, .b = 0.5 });
  auto center = (point3){ .x = 0.0, .y = -1000.0, .z = 0.0 };
  auto s      = sphere_new (center, center, 1000.0, (mat_t *)m);
  CHECK_MEMORY;
  arrput (g_world->hittables, (hittable_t *)s);
}

static void
create_big_spheres ()
{
  {
    auto m      = dielectric_new (1.50);
    auto center = (point3){ .x = 0, .y = 1, .z = 0 };
    auto s      = sphere_new (center, center, 1.0, (mat_t *)m);
    CHECK_MEMORY;
    arrput (g_world->hittables, (hittable_t *)s);
  }
  {
    auto m      = lambertian_new ((color_t){ .r = 0.4, .g = 0.2, .b = 0.1 });
    auto center = (point3){ .x = -4, .y = 1, .z = 0 };
    auto s      = sphere_new (center, center, 1.0, (mat_t *)m);
    CHECK_MEMORY;
    arrput (g_world->hittables, (hittable_t *)s);
  }
  {
    auto m      = metal_new ((color_t){ .r = 0.7, .g = 0.6, .b = 0.5 }, 0.0);
    auto center = (point3){ .x = 4, .y = 1, .z = 0 };
    auto s      = sphere_new (center, center, 1.0, (mat_t *)m);
    CHECK_MEMORY;
    arrput (g_world->hittables, (hittable_t *)s);
  }
}

// Create small spheres randomly.
static void
create_small_spheres ()
{
  int const n = 11;

  for (int a = -n; a < n; a++)
    {
      for (int b = -n; b < n; b++)
        {
          auto matte        = random_double ();
          auto center_start = (point3){ .x = a + 0.9 * random_double (), .y = 0.2, .z = b + 0.9 * random_double () };
          auto dist_from_center = vec3_length (vec3_sub (center_start, (point3){ .x = 4, .y = 0.2, .z = 0 }));

          if (dist_from_center > 0.9)
            {
              if (matte < 0.8)
                {
                  // diffuse
                  auto albedo     = vec3_mulv (vec3_random (), vec3_random ());
                  auto m          = lambertian_new (albedo);
                  auto y_rnd      = random_double_min_max (0, .5);
                  auto center_end = vec3_add (center_start, (vec3_t){ .x = 0, .y = y_rnd, .z = 0 });
                  auto s          = sphere_new (center_start, center_end, 0.2, (material_t *)m);
                  CHECK_MEMORY;
                  arrput (g_world->hittables, (hittable_t *)s);
                }
              else if (matte < 0.95)
                {
                  // metal
                  auto albedo = vec3_random_min_max (0.5, 1);
                  auto fuzz   = random_double_min_max (0, 0.5);
                  auto m      = metal_new (albedo, fuzz);
                  auto s      = sphere_new (center_start, center_start, 0.2, (material_t *)m);
                  CHECK_MEMORY;
                  arrput (g_world->hittables, (hittable_t *)s);
                }
              else
                {
                  // glass
                  auto m = dielectric_new (1.5);
                  auto s = sphere_new (center_start, center_start, 0.2, (material_t *)m);
                  CHECK_MEMORY;
                  arrput (g_world->hittables, (hittable_t *)s);
                }
            }
        }
    }
}

static void
init_g_world ()
{
  g_world = hittable_list_new ();
  if (!g_world)
    {
      logExit ("Out of memory");
    }
}

void
world_init (void)
{
  init_g_world ();
  create_ground ();
  create_big_spheres ();
  create_small_spheres ();
}

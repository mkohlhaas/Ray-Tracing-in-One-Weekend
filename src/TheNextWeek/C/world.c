#include "world.h"
#include "bvh_node.h"
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
hittable_list_t *g_world = NULL;
bvh_node_t      *world   = NULL;

#define CHECK_MEMORY                                                                                                   \
  if (!m || !s)                                                                                                        \
    {                                                                                                                  \
      logExit ("Out of memory");                                                                                       \
    }

// Ground is a just a very huge sphere.
static void
create_ground ()
{
  auto m = lambertian_new ((color_t){ .r = 0.5, .g = 0.5, .b = 0.5 });
  auto c = (point3_t){ .x = 0.0, .y = -1000.0, .z = 0.0 };
  auto s = sphere_new (c, c, 1000.0, (mat_t *)m);
  CHECK_MEMORY;
  hittable_list_add (g_world, (hittable_t *)s);
}

static void
create_big_spheres ()
{
  {
    auto m = dielectric_new (1.50);
    auto c = (point3_t){ .x = 0, .y = 1, .z = 0 };
    auto s = sphere_new (c, c, 1.0, (mat_t *)m);
    CHECK_MEMORY;
    hittable_list_add (g_world, (hittable_t *)s);
  }

  {
    auto m = lambertian_new ((color_t){ .r = 0.4, .g = 0.2, .b = 0.1 });
    auto c = (point3_t){ .x = -4, .y = 1, .z = 0 };
    auto s = sphere_new (c, c, 1.0, (mat_t *)m);
    CHECK_MEMORY;
    hittable_list_add (g_world, (hittable_t *)s);
  }

  {
    auto m = metal_new ((color_t){ .r = 0.7, .g = 0.6, .b = 0.5 }, 0.0);
    auto c = (point3_t){ .x = 4, .y = 1, .z = 0 };
    auto s = sphere_new (c, c, 1.0, (mat_t *)m);
    CHECK_MEMORY;
    hittable_list_add (g_world, (hittable_t *)s);
  }
}

// Create small spheres randomly.
static void
create_small_spheres ()
{
  int const n = 3;

  for (int a = -n; a < n; a++)
    {
      for (int b = -n; b < n; b++)
        {
          auto matte   = random_double ();
          auto c_start = (point3_t){ .x = a + 0.9 * random_double (), .y = 0.2, .z = b + 0.9 * random_double () };
          auto dist_from_center = vec3_length (vec3_sub (c_start, (point3_t){ .x = 4, .y = 0.2, .z = 0 }));

          if (dist_from_center > 0.9)
            {
              if (matte < 0.8)
                {
                  // diffuse
                  auto albedo = vec3_mulv (vec3_random (), vec3_random ());
                  auto m      = lambertian_new (albedo);
                  auto y_rnd  = random_double_min_max (0, .5);
                  auto c_end  = vec3_add (c_start, (vec3_t){ .x = 0, .y = y_rnd, .z = 0 });
                  auto s      = sphere_new (c_start, c_end, 0.2, (material_t *)m);
                  CHECK_MEMORY;
                  hittable_list_add (g_world, (hittable_t *)s);
                }
              else if (matte < 0.95)
                {
                  // metal
                  auto albedo = vec3_random_min_max (0.5, 1);
                  auto fuzz   = random_double_min_max (0, 0.5);
                  auto m      = metal_new (albedo, fuzz);
                  auto s      = sphere_new (c_start, c_start, 0.2, (material_t *)m);
                  CHECK_MEMORY;
                  hittable_list_add (g_world, (hittable_t *)s);
                }
              else
                {
                  // glass
                  auto m = dielectric_new (1.5);
                  auto s = sphere_new (c_start, c_start, 0.2, (material_t *)m);
                  CHECK_MEMORY;
                  hittable_list_add (g_world, (hittable_t *)s);
                }
            }
        }
    }
}

static void
create_bvh ()
{
  world = bvh_node_new (g_world->hittables);
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
  // create_ground ();
  create_big_spheres ();
  create_small_spheres ();
  create_bvh ();
  print_bvh (world, 0);
}

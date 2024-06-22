#include "dielectric.h"
#include "lambertian.h"
#include "metal.h"
#include "point.h"
#include "sphere.h"
#include "stb_ds.h"
#include "utils.h"

// global world
hit_able_t **g_world = NULL;

// Ground is a just a very huge sphere.
static void
create_ground ()
{
  auto m_ground = lambertian_new ((color_t){ .r = 0.5, .g = 0.5, .b = 0.5 });
  auto s_ground = sphere_new ((point3){ .x = 0.0, .y = -1000.0, .z = 0.0 }, 1000.0, (mat_t *)m_ground);
  arrput (g_world, (hit_able_t *)s_ground);
}

static void
create_big_spheres ()
{
  // materials
  auto m1 = dielectric_new (1.50);
  auto m2 = lambertian_new ((color_t){ .r = 0.4, .g = 0.2, .b = 0.1 });
  auto m3 = metal_new ((color_t){ .r = 0.7, .g = 0.6, .b = 0.5 }, 0.0);

  // spheres
  auto s1 = sphere_new ((point3){ .x = 0, .y = 1, .z = 0 }, 1.0, (mat_t *)m1);
  auto s2 = sphere_new ((point3){ .x = -4, .y = 1, .z = 0 }, 1.0, (mat_t *)m2);
  auto s3 = sphere_new ((point3){ .x = 4, .y = 1, .z = 0 }, 1.0, (mat_t *)m3);

  arrput (g_world, (hit_able_t *)s1);
  arrput (g_world, (hit_able_t *)s2);
  arrput (g_world, (hit_able_t *)s3);
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
          auto matte  = random_double ();
          auto center = (point3){ .x = a + 0.9 * random_double (), .y = 0.2, .z = b + 0.9 * random_double () };
          auto dist_from_center = vec3_length (vec3_sub (center, (point3){ .x = 4, .y = 0.2, .z = 0 }));

          if (dist_from_center > 0.9)
            {
              if (matte < 0.8)
                {
                  // diffuse
                  auto albedo = vec3_mul (vec3_random (), vec3_random ());
                  auto m      = lambertian_new (albedo);
                  auto s      = sphere_new (center, 0.2, (material_t *)m);
                  arrput (g_world, (hit_able_t *)s);
                }
              else if (matte < 0.95)
                {
                  // metal
                  auto albedo = vec3_random_min_max (0.5, 1);
                  auto fuzz   = random_double_min_max (0, 0.5);
                  auto m      = metal_new (albedo, fuzz);
                  auto s      = sphere_new (center, 0.2, (material_t *)m);
                  arrput (g_world, (hit_able_t *)s);
                }
              else
                {
                  // glass
                  auto m = dielectric_new (1.5);
                  auto s = sphere_new (center, 0.2, (material_t *)m);
                  arrput (g_world, (hit_able_t *)s);
                }
            }
        }
    }
}

void
world_init (void)
{
  create_ground ();
  create_big_spheres ();
  create_small_spheres ();
}

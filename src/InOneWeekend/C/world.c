#include "dielectric.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"
#include "stb_ds.h"
#include "utils.h"

hit_able_t **world = NULL;

void
world_init (void)
{
  lambertian_t *material_ground = lambertian_new ((color_t){ .r = 0.5, .g = 0.5, .b = 0.5 });
  sphere_t     *s1 = sphere_new ((point3){ .x = 0.0, .y = -1000.0, .z = 0.0 }, 1000.0, (material_t *)material_ground);
  arrput (world, (hit_able_t *)s1);

  dielectric_t *material1 = dielectric_new (1.50);
  sphere_t     *s2        = sphere_new ((point3){ .x = 0, .y = 1, .z = 0 }, 1.0, (material_t *)material1);
  arrput (world, (hit_able_t *)s2);

  lambertian_t *material2 = lambertian_new ((color_t){ .r = 0.4, .g = 0.2, .b = 0.1 });
  sphere_t     *s3        = sphere_new ((point3){ .x = -4, .y = 1, .z = 0 }, 1.0, (material_t *)material2);
  arrput (world, (hit_able_t *)s3);

  metal    *material3 = metal_new ((color_t){ .r = 0.7, .g = 0.6, .b = 0.5 }, 0.0);
  sphere_t *s4        = sphere_new ((point3){ .x = 4, .y = 1, .z = 0 }, 1.0, (material_t *)material3);
  arrput (world, (hit_able_t *)s4);

  for (int a = -11; a < 11; a++)
    {
      for (int b = -11; b < 11; b++)
        {
          auto choose_mat = random_double ();
          auto center     = (point3){ .x = a + 0.9 * random_double (), .y = 0.2, .z = b + 0.9 * random_double () };

          if (vec3_length (vec3_sub (center, (point3){ .x = 4, .y = 0.2, .z = 0 })) > 0.9)
            {
              // shared_ptr<material> sphere_material;

              if (choose_mat < 0.8)
                {
                  // diffuse
                  vec3_t        albedo = vec3_mul (vec3_random (), vec3_random ());
                  lambertian_t *m      = lambertian_new (albedo);
                  sphere_t     *s      = sphere_new (center, 0.2, (material_t *)m);
                  arrput (world, (hit_able_t *)s);
                }
              else if (choose_mat < 0.95)
                {
                  // metal
                  vec3_t    albedo = vec3_random_min_max (0.5, 1);
                  double    fuzz   = random_double_min_max (0, 0.5);
                  metal    *m      = metal_new (albedo, fuzz);
                  sphere_t *s      = sphere_new (center, 0.2, (material_t *)m);
                  arrput (world, (hit_able_t *)s);
                }
              else
                {
                  // glass
                  dielectric_t *m = dielectric_new (1.5);
                  sphere_t     *s = sphere_new (center, 0.2, (material_t *)m);
                  arrput (world, (hit_able_t *)s);
                }
            }
        }
    }
}

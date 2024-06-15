#include "color.h"
#include "dielectric.h"
#include "hittable.h"
#include "lambertian.h"
#include "material.h"
#include "metal.h"
#include "sphere.h"
#include "stb_ds.h"
#include "utils.h"
#include "vec3.h"

hittable **world = NULL;

void
world_init (void)
{
  lambertian *material_ground = lambertian_new ((color){ .r = 0.5, .g = 0.5, .b = 0.5 });
  sphere     *s1  = sphere_new ((point3){ .x = 0.0, .y = -1000.0, .z = 0.0 }, 1000.0, (material *)material_ground);
  hittable   *sh1 = hittable_new (sphere_hit, s1);
  arrput (world, sh1);

  dielectric *material1 = dielectric_new (1.50);
  sphere     *s2        = sphere_new ((point3){ .x = 0, .y = 1, .z = 0 }, 1.0, (material *)material1);
  hittable   *sh2       = hittable_new (sphere_hit, s2);
  arrput (world, sh2);

  lambertian *material2 = lambertian_new ((color){ .r = 0.4, .g = 0.2, .b = 0.1 });
  sphere     *s3        = sphere_new ((point3){ .x = -4, .y = 1, .z = 0 }, 1.0, (material *)material2);
  hittable   *sh3       = hittable_new (sphere_hit, s3);
  arrput (world, sh3);

  metal    *material3 = metal_new ((color){ .r = 0.7, .g = 0.6, .b = 0.5 }, 0.0);
  sphere   *s4        = sphere_new ((point3){ .x = 4, .y = 1, .z = 0 }, 1.0, (material *)material3);
  hittable *sh4       = hittable_new (sphere_hit, s4);
  arrput (world, sh4);

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
                  vec3        albedo = vec3_mul (vec3_random (), vec3_random ());
                  lambertian *m      = lambertian_new (albedo);
                  sphere     *s      = sphere_new (center, 0.2, (material *)m);
                  hittable   *sh     = hittable_new (sphere_hit, s);
                  arrput (world, sh);
                }
              else if (choose_mat < 0.95)
                {
                  // metal
                  vec3      albedo = vec3_random_min_max (0.5, 1);
                  double    fuzz   = random_double_min_max (0, 0.5);
                  metal    *m      = metal_new (albedo, fuzz);
                  sphere   *s      = sphere_new (center, 0.2, (material *)m);
                  hittable *sh     = hittable_new (sphere_hit, s);
                  arrput (world, sh);
                }
              else
                {
                  // glass
                  dielectric *m  = dielectric_new (1.5);
                  sphere     *s  = sphere_new (center, 0.2, (material *)m);
                  hittable   *sh = hittable_new (sphere_hit, s);
                  arrput (world, sh);
                }
            }
        }
    }
}

#include "hittable.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"
#include <glib.h>
#include <stdio.h>

int
main (void)
{
  // image
  double aspect_ratio_demand = 16.0 / 9.0;
  int    image_width         = 1200;

  // Calculate the image height, and ensure that it's at least 1.
  int image_height = image_width / aspect_ratio_demand;
  image_height     = image_height < 1 ? 1 : image_height;

  // world
  GArray *world = g_array_new (FALSE, FALSE, sizeof (hittable));

  sphere   S1  = { (point3){ .x = 0, .y = 0, .z = -1}, 0.5 };
  hittable SH1 = { hit_sphere, &S1 };
  g_array_append_val (world, SH1);

  sphere   S2  = { (point3){ .x = 0, .y = -100.5, .z = -1}, 100 };
  hittable SH2 = { hit_sphere, &S2 };
  g_array_append_val (world, SH2);

  // camera
  double focal_length      = 1.0; // distance camera to viewport
  double viewport_height   = 2.0;
  double aspect_ratio_real = (double)image_width / image_height;
  double viewport_width    = viewport_height * aspect_ratio_real;
  point3 camera_center     = origin;

  // Calculate the vectors across the horizontal and down the vertical viewport edges in x-y plane.
  vec3 viewport_u = { .x = viewport_width };
  vec3 viewport_v = { .y = -viewport_height };

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  vec3 pixel_delta_u = vec3_scalar_div (viewport_u, image_width);
  vec3 pixel_delta_v = vec3_scalar_div (viewport_v, image_height);

  vec3 viewport_center       = vec3_add (viewport_u, viewport_v);
  viewport_center            = vec3_scalar_div (viewport_center, 2.0);
  viewport_center            = vec3_add ((vec3){ .z = focal_length }, viewport_center);
  point3 viewport_upper_left = vec3_sub (camera_center, viewport_center);
  vec3   pixel_center        = vec3_add (pixel_delta_u, pixel_delta_v);
  pixel_center               = vec3_scalar_div (pixel_center, 2.0);
  point3 pixel_origin        = vec3_add (viewport_upper_left, pixel_center);

  // rendering
  // write image file header
  printf ("P3\n%d %d\n255\n", image_width, image_height);

  // write image
  for (int row = 0; row < image_height; row++)
    {
      fprintf (stderr, "\rScanlines remaining: %d", image_height - row);
      for (int col = 0; col < image_width; col++)
        {
          vec3   pixel_u             = vec3_scalar_mult (pixel_delta_u, col);
          vec3   pixel_v             = vec3_scalar_mult (pixel_delta_v, row);
          vec3   pixel               = vec3_add (pixel_u, pixel_v);
          point3 pixel_center        = vec3_add (pixel_origin, pixel);
          vec3   ray_direction       = vec3_sub (pixel_center, camera_center);
          ray    ray_camera_to_pixel = { .origin = camera_center, .direction = ray_direction };
          color  pixel_color         = ray_color (ray_camera_to_pixel, world);
          write_color (stdout, pixel_color);
        }
    }
  fprintf (stderr, "\rDone.                                   \n");

  g_array_free (world, FALSE);
}

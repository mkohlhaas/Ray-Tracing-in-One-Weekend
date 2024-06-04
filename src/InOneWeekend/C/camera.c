#include "camera.h"
#include "ray.h"

camera cam;

void
camera_init (void)
{
  cam = (camera){
    .aspect_ratio    = 16.0 / 9.0,
    .image_width     = 1200,
    .focal_length    = 1.0,
    .viewport_height = 2.0,
    .center          = origin,
  };

  cam.image_height   = cam.image_width / cam.aspect_ratio;
  cam.image_height   = cam.image_height < 1 ? 1 : cam.image_height;
  cam.aspect_ratio   = (double)cam.image_width / cam.image_height;
  cam.viewport_width = cam.viewport_height * cam.aspect_ratio;

  vec3 viewport_u         = { .x = cam.viewport_width };
  vec3 viewport_v         = { .y = -cam.viewport_height };
  cam.pixel_delta_u       = vec3_scalar_div (viewport_u, cam.image_width);
  cam.pixel_delta_v       = vec3_scalar_div (viewport_v, cam.image_height);
  vec3 viewport_center    = vec3_add (viewport_u, viewport_v);
  viewport_center         = vec3_scalar_div (viewport_center, 2.0);
  viewport_center         = vec3_add ((vec3){ .z = cam.focal_length }, viewport_center);
  cam.viewport_upper_left = vec3_sub (cam.center, viewport_center);
  vec3 pixel_center       = vec3_add (cam.pixel_delta_u, cam.pixel_delta_v);
  pixel_center            = vec3_scalar_div (pixel_center, 2.0);
  cam.pixel_origin        = vec3_add (cam.viewport_upper_left, pixel_center);
}

void
render (camera c, GArray *const world)
{
  // write pnm header
  printf ("P3\n%d %d\n255\n", c.image_width, c.image_height);

  // write image
  for (int row = 0; row < c.image_height; row++)
    {
      fprintf (stderr, "\rScanlines remaining: %d", c.image_height - row);
      for (int col = 0; col < c.image_width; col++)
        {
          vec3   pixel_u             = vec3_scalar_mult (c.pixel_delta_u, col);
          vec3   pixel_v             = vec3_scalar_mult (c.pixel_delta_v, row);
          vec3   pixel               = vec3_add (pixel_u, pixel_v);
          point3 pixel_center        = vec3_add (c.pixel_origin, pixel);
          vec3   ray_direction       = vec3_sub (pixel_center, c.center);
          ray    ray_camera_to_pixel = { .origin = c.center, .direction = ray_direction };
          color  pixel_color         = ray_color (ray_camera_to_pixel, world);
          write_color (stdout, pixel_color);
        }
    }
  fprintf (stderr, "\rDone.                                   \n");
}

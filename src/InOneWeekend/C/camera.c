#include "camera.h"
#include "ray.h"
#include "utils.h"
#include <math.h>

camera_t cam;

void
camera_init (void)
{
  cam = (camera_t){
    .aspect_ratio      = 16.0 / 9.0,
    .image_width       = 240,
    .viewport_height   = 2.0,
    .samples_per_pixel = 500,
    .max_depth         = 50,
    .vfov              = 5,
    .lookat            = origin,
    .lookfrom          = (point3){ .x = 13, .y = 2, .z = 3 },
    .vup               = (vec3_t){ .x = 0, .y = 1, .z = 0 },
    .defocus_angle     = 0.6,
    .focus_dist        = 10.0,
  };

  cam.image_height        = cam.image_width / cam.aspect_ratio;
  cam.image_height        = cam.image_height < 1 ? 1 : cam.image_height;
  cam.aspect_ratio        = (double)cam.image_width / cam.image_height;
  cam.pixel_samples_scale = 1.0 / cam.samples_per_pixel;
  // cam.focal_length        = vec3_length (vec3_sub (cam.lookfrom, cam.lookat));
  double theta        = degrees_to_radians (cam.vfov);
  double h            = tan (theta / 2);
  cam.viewport_height = 2 * h * cam.focus_dist;
  cam.viewport_width  = cam.viewport_height * cam.image_width / cam.image_height;

  // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
  cam.w = vec3_unit (vec3_sub (cam.lookfrom, cam.lookat));
  cam.u = vec3_unit (vec3_cross (cam.vup, cam.w));
  cam.v = vec3_cross (cam.w, cam.u);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  vec3_t viewport_u = vec3_scalar_mult (cam.u, cam.viewport_width); // Vector across viewport horizontal edge
  vec3_t viewport_v = vec3_scalar_mult (vec3_minus (cam.v), cam.viewport_height); // Vector down viewport vertical edge

  cam.pixel_delta_u       = vec3_scalar_div (viewport_u, cam.image_width);
  cam.pixel_delta_v       = vec3_scalar_div (viewport_v, cam.image_height);
  cam.viewport_upper_left = vec3_sub (
      vec3_sub (vec3_sub (cam.lookfrom, vec3_scalar_mult (cam.w, cam.focus_dist)), vec3_scalar_div (viewport_u, 2)),
      vec3_scalar_div (viewport_v, 2));
  vec3_t pixel_center = vec3_add (cam.pixel_delta_u, cam.pixel_delta_v);
  pixel_center        = vec3_scalar_div (pixel_center, 2.0);
  cam.pixel_origin    = vec3_add (cam.viewport_upper_left, pixel_center);

  // Calculate the camera defocus disk basis vectors.
  double defocus_radius = cam.focus_dist * tan (degrees_to_radians (cam.defocus_angle / 2));
  cam.defocus_disk_u    = vec3_scalar_mult (cam.u, defocus_radius);
  cam.defocus_disk_v    = vec3_scalar_mult (cam.v, defocus_radius);
}

void
render (camera_t cam, hit_able_t **world)
{
  // write pnm header
  printf ("P3\n%d %d\n255\n", cam.image_width, cam.image_height);

  // write image
  for (int row = 0; row < cam.image_height; row++)
    {
      fprintf (stderr, "\rScanlines remaining: %6d", cam.image_height - row);
      for (int col = 0; col < cam.image_width; col++)
        {
          color_t pixel_color = black;
          for (int sample = 0; sample < cam.samples_per_pixel; sample++)
            {
              ray_t r     = get_ray (cam, row, col);
              pixel_color = vec3_add (pixel_color, ray_color (r, cam.max_depth, world));
            }
          write_color (stdout, vec3_scalar_mult (pixel_color, cam.pixel_samples_scale));
        }
    }
  fprintf (stderr, "\rDone.                                   \n");
}

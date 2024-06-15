#include "camera.h"
#include "color.h"
#include "point.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>

camera cam;

void
camera_init (void)
{
  cam = (camera){
    .aspect_ratio      = 16.0 / 9.0,
    .image_width       = 1200,
    .viewport_height   = 2.0,
    .samples_per_pixel = 100,
    .max_depth         = 10,
    .vfov              = 20,
    .lookfrom          = (point3){ .x = -2, .y = 2, .z = 1 },
    .lookat            = (point3){ .x = 0, .y = 0, .z = -1 },
    .vup               = (vec3){ .x = 0, .y = 1, .z = 0 },
    .defocus_angle     = 10.0,
    .focus_dist        = 3.4,
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
  cam.u = vec3_unit (vec3_cross_product (cam.vup, cam.w));
  cam.v = vec3_cross_product (cam.w, cam.u);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  vec3 viewport_u = vec3_scalar_mult (cam.u, cam.viewport_width); // Vector across viewport horizontal edge
  vec3 viewport_v = vec3_scalar_mult (vec3_minus (cam.v), cam.viewport_height); // Vector down viewport vertical edge

  cam.pixel_delta_u = vec3_scalar_div (viewport_u, cam.image_width);
  cam.pixel_delta_v = vec3_scalar_div (viewport_v, cam.image_height);
  // vec3 viewport_center    = vec3_add (viewport_u, viewport_v);
  // viewport_center         = vec3_scalar_div (viewport_center, 2.0);
  // viewport_center         = vec3_add ((vec3){ .z = cam.focus_dist }, viewport_center);
  cam.viewport_upper_left = vec3_sub (
      vec3_sub (vec3_sub (cam.lookfrom, vec3_scalar_mult (cam.w, cam.focus_dist)), vec3_scalar_div (viewport_u, 2)),
      vec3_scalar_div (viewport_v, 2));
  vec3 pixel_center = vec3_add (cam.pixel_delta_u, cam.pixel_delta_v);
  pixel_center      = vec3_scalar_div (pixel_center, 2.0);
  cam.pixel_origin  = vec3_add (cam.viewport_upper_left, pixel_center);

  // Calculate the camera defocus disk basis vectors.
  auto defocus_radius = cam.focus_dist * tan (degrees_to_radians (cam.defocus_angle / 2));
  cam.defocus_disk_u  = vec3_scalar_mult (cam.u, defocus_radius);
  cam.defocus_disk_v  = vec3_scalar_mult (cam.v, defocus_radius);
}

void
render (camera cam, struct hittable **world)
{
  // write pnm header
  printf ("P3\n%d %d\n255\n", cam.image_width, cam.image_height);

  // write image
  for (int row = 0; row < cam.image_height; row++)
    {
      fprintf (stderr, "\rScanlines remaining: %6d", cam.image_height - row);
      for (int col = 0; col < cam.image_width; col++)
        {
          color pixel_color = black;
          for (int sample = 0; sample < cam.samples_per_pixel; sample++)
            {
              ray r       = get_ray (cam, row, col);
              pixel_color = vec3_add (pixel_color, ray_color (r, cam.max_depth, world));
            }
          write_color (stdout, vec3_scalar_mult (pixel_color, cam.pixel_samples_scale));
        }
    }
  fprintf (stderr, "\rDone.                                   \n");
}

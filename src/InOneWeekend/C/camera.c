#include "camera.h"
#include "camera_defs.h"
#include "ray.h"
#include "utils.h"
#include "world.h"
#include <math.h>

// global camera
camera_t g_camera;

static void
camera_defaults ()
{
  g_camera = (camera_t){
    .image_width       = IMAGE_WIDTH,
    .image_height      = IMAGE_HEIGHT,
    .samples_per_pixel = SAMPLES_PER_PIXEL,
    .max_depth         = MAX_DEPTH,
    .lookat            = LOOKAT,
    .lookfrom          = LOOKFROM,
    .defocus_angle     = DEFOCUS_ANGLE,
  };
}

void
camera_init (void)
{
  camera_defaults ();
  double focus_dist = FOCUS_DIST;
  double vfov       = VFOV;
  point3 vup        = VUP;

  // Calculate image height
  // g_camera.image_height = g_camera.image_width / aspect_ratio;
  // g_camera.image_height = g_camera.image_height < 1 ? 1 : g_camera.image_height;

  // Calculate viewport width and height
  auto theta           = degrees_to_radians (vfov);
  auto h               = tan (theta / 2);
  auto viewport_height = 2 * h * focus_dist;
  auto viewport_width  = viewport_height * ASPECT_RATIO;

  // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
  auto w = vec3_unit (vec3_sub (g_camera.lookfrom, g_camera.lookat));
  auto u = vec3_unit (vec3_cross (vup, w));
  auto v = vec3_cross (w, u);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  vec3_t viewport_u = vec3_mult (u, viewport_width);
  vec3_t viewport_v = vec3_mult (vec3_minus (v), viewport_height);

  // TODO: clean up this mess
  auto viewport_upper_left
      = vec3_sub (vec3_sub (vec3_sub (g_camera.lookfrom, vec3_mult (w, focus_dist)), vec3_divt (viewport_u, 2)),
                  vec3_divt (viewport_v, 2));

  // Calculate pixel origin and pixel u, v  vectors.
  g_camera.pixel_delta_u = vec3_divt (viewport_u, g_camera.image_width);
  g_camera.pixel_delta_v = vec3_divt (viewport_v, g_camera.image_height);
  auto pixel_center      = vec3_add (g_camera.pixel_delta_u, g_camera.pixel_delta_v);
  pixel_center           = vec3_divt (pixel_center, 2.0);
  g_camera.pixel_origin  = vec3_add (viewport_upper_left, pixel_center);

  // Calculate the camera defocus disk basis vectors.
  auto defocus_radius     = focus_dist * tan (degrees_to_radians (g_camera.defocus_angle / 2));
  g_camera.defocus_disk_u = vec3_mult (u, defocus_radius);
  g_camera.defocus_disk_v = vec3_mult (v, defocus_radius);
}

static void
write_ppm_header ()
{
  printf ("P3\n%d %d\n255\n", g_camera.image_width, g_camera.image_height);
}

static void
write_image_body ()
{
  for (int row = 0; row < g_camera.image_height; row++)
    {
      fprintf (stderr, "\rScanlines remaining: %6d", g_camera.image_height - row);
      for (int col = 0; col < g_camera.image_width; col++)
        {
          color_t pixel_color = black;
          for (int sample = 0; sample < g_camera.samples_per_pixel; sample++)
            {
              auto ray     = random_ray (g_camera, row, col);
              auto ray_col = ray_color (ray, g_camera.max_depth, g_world);
              pixel_color  = vec3_add (pixel_color, ray_col);
            }
          auto color_res = vec3_divt (pixel_color, g_camera.samples_per_pixel);
          write_color (stdout, color_res);
        }
    }
  fprintf (stderr, "\rDone.                                   \n");
}

void
render ()
{
  write_ppm_header ();
  write_image_body ();
}

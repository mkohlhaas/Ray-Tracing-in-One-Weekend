#include "camera.h"
#include "args.h"
#include "camera_defs.h"
#include "globals.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"
#include "world.h"
#include <math.h>

// global camera
camera_t g_camera;

static void
camera_defaults ()
{
  g_camera = (camera_t){
    .samples_per_pixel = SAMPLES_PER_PIXEL,
    .max_depth         = MAX_DEPTH,
    .lookat            = LOOKAT,
    .lookfrom          = LOOKFROM,
    .defocus_angle     = DEFOCUS_ANGLE,
  };
}

static vec3_t
calc_viewport_upper_left (vec3_t w, double focus_dist, vec3_t viewport_u, vec3_t viewport_v)
{
  auto vtmp1 = vec3_mult (focus_dist, w);
  auto vtmp2 = vec3_sub (g_camera.lookfrom, vtmp1);
  auto vtmp3 = vec3_divt (viewport_u, 2);
  auto vtmp4 = vec3_divt (viewport_v, 2);
  auto vtmp5 = vec3_sub (vtmp2, vtmp3);
  return vec3_sub (vtmp5, vtmp4);
}

void
camera_init (void)
{
  camera_defaults ();
  double   focus_dist = FOCUS_DIST;
  double   vfov       = VFOV; // vertical field of view in degrees
  point3_t vup        = VUP;

  // Calculate viewport width and height
  auto aspect_ratio    = (double)args.image_width / args.image_height;
  auto theta           = degrees_to_radians (vfov);
  auto h               = tan (theta / 2);
  auto viewport_height = 2 * h * focus_dist;
  auto viewport_width  = viewport_height * aspect_ratio;

  // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
  auto w = vec3_unit (vec3_sub (g_camera.lookfrom, g_camera.lookat));
  auto u = vec3_unit (vec3_cross (vup, w));
  auto v = vec3_cross (w, u);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  auto viewport_u          = vec3_mult (viewport_width, u);
  auto viewport_v          = vec3_mult (viewport_height, vec3_uminus (v));
  auto viewport_upper_left = calc_viewport_upper_left (w, focus_dist, viewport_u, viewport_v);

  // Calculate pixel origin and pixel u, v  vectors.
  g_camera.pixel_delta_u = vec3_divt (viewport_u, args.image_width);
  g_camera.pixel_delta_v = vec3_divt (viewport_v, args.image_height);
  auto pixel_center      = vec3_add (g_camera.pixel_delta_u, g_camera.pixel_delta_v);
  pixel_center           = vec3_divt (pixel_center, 2.0);
  g_camera.pixel_origin  = vec3_add (viewport_upper_left, pixel_center);

  // Calculate the camera defocus disk basis vectors.
  auto defocus_radius     = focus_dist * tan (degrees_to_radians (g_camera.defocus_angle / 2));
  g_camera.defocus_disk_u = vec3_mult (defocus_radius, u);
  g_camera.defocus_disk_v = vec3_mult (defocus_radius, v);
}

static void
write_ppm_header ()
{
  fprintf (g_output_file, "P3\n%d %d\n255\n", args.image_width, args.num_scanlines);
}

static void
print_num_remaining_scanlines (int row)
{
  fprintf (stderr, "\rScanlines remaining: %6d", args.num_scanlines - (row - args.start_scanline));
}

static void
print_done (void)
{
  fprintf (stderr, "\rDone.                                   \n");
}

static void
render_image_body ()
{
  for (int row = args.start_scanline; row < args.start_scanline + args.num_scanlines; row++)
    {
      print_num_remaining_scanlines (row);
      for (int col = 0; col < args.image_width; col++)
        {
          color_t pixel_col = black;
          for (int sample = 0; sample < g_camera.samples_per_pixel; sample++)
            {
              auto ray     = random_ray (g_camera, row, col);
              auto ray_col = ray_color (ray, g_camera.max_depth, (hittable_t *)world);
              pixel_col    = vec3_add (pixel_col, ray_col);
            }
          auto color = vec3_divt (pixel_col, g_camera.samples_per_pixel);
          write_color (g_output_file, color);
        }
    }
  print_done ();
}

void
render ()
{
  write_ppm_header ();
  render_image_body ();
}

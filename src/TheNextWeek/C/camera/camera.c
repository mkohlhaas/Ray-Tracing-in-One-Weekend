#include "camera/camera.h"
#include "args/args.h"
#include "globals/globals.h"
#include "math/vec3.h"
#include "ray/ray.h"
#include "utils/utils.h"
#include "world/world.h"
#include <math.h>
#include <stdio.h>

static void
camera_defaults ()
{
  g_camera = (camera_t){
    .samples_per_pixel = g_samples_per_pixel,
    .max_depth         = g_max_depth,
    .lookat            = g_lookat,
    .lookfrom          = g_lookfrom,
    .defocus_angle     = g_defocus_angle,
    .focus_dist        = g_focus_dist,
  };
}

static vec3_t
calc_viewport_upper_left (vec3_t w, vec3_t viewport_u, vec3_t viewport_v)
{
  auto vtmp1 = vec3_mult (g_focus_dist, w);
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

  // Calculate viewport width and height
  auto aspect_ratio    = (double)args.image_width / args.image_height;
  auto theta           = degrees_to_radians (g_vfov);
  auto h               = tan (theta / 2);
  auto viewport_height = 2 * h * g_focus_dist;
  auto viewport_width  = viewport_height * aspect_ratio;

  // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
  auto w = vec3_unit (vec3_sub (g_camera.lookfrom, g_camera.lookat));
  auto u = vec3_unit (vec3_cross (g_vup, w));
  auto v = vec3_cross (w, u);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  auto viewport_u          = vec3_mult (viewport_width, u);
  auto viewport_v          = vec3_mult (viewport_height, vec3_uminus (v));
  auto viewport_upper_left = calc_viewport_upper_left (w, viewport_u, viewport_v);

  // Calculate pixel origin and pixel u, v  vectors.
  g_camera.pixel_delta_u = vec3_divt (viewport_u, args.image_width);
  g_camera.pixel_delta_v = vec3_divt (viewport_v, args.image_height);
  auto pixel_center      = vec3_add (g_camera.pixel_delta_u, g_camera.pixel_delta_v);
  pixel_center           = vec3_divt (pixel_center, 2.0);
  g_camera.pixel_origin  = vec3_add (viewport_upper_left, pixel_center);

  // Calculate the camera defocus disk basis vectors.
  auto defocus_radius     = g_focus_dist * tan (degrees_to_radians (g_camera.defocus_angle / 2));
  g_camera.defocus_disk_u = vec3_mult (defocus_radius, u);
  g_camera.defocus_disk_v = vec3_mult (defocus_radius, v);
}

static void
write_ppm_header (FILE *output_file)
{
  fprintf (output_file, "P3\n%d %d\n255\n", args.image_width, args.num_scanlines);
}

static void
print_done (void)
{
  fprintf (stderr, ".");
}

static void
render_image_body (FILE *output_file)
{
  for (int row = args.start_scanline; row < args.start_scanline + args.num_scanlines; row++)
    {
      for (int col = 0; col < args.image_width; col++)
        {
          color_t pixel_col = black;
          for (int sample = 0; sample < g_camera.samples_per_pixel; sample++)
            {
              auto ray = random_ray (g_camera, row, col);
              // auto ray_col = ray_color (ray, g_camera.max_depth, (hittable_t *)g_world_bvh);
              auto ray_col = ray_color (ray, g_camera.max_depth, (hittable_t *)g_world_list);
              pixel_col    = vec3_add (pixel_col, ray_col);
            }
          auto color = vec3_divt (pixel_col, g_camera.samples_per_pixel);
          color_write (output_file, color);
        }
    }
  print_done ();
}

void
render (FILE *output_file)
{
  write_ppm_header (output_file);
  render_image_body (output_file);
}

void
print_global_camera ()
{
  camera_t c = g_camera;
  fprintf (stderr, "Global camera:\n");
  fprintf (stderr, "Samples per Pixel: %d\n", c.samples_per_pixel);
  fprintf (stderr, "Focus distance:    %f\n", c.focus_dist);
  fprintf (stderr, "Max depth:         %d\n", c.max_depth);
  fprintf (stderr, "Defocus angle:     %f\n", c.defocus_angle);
  fprintf (stderr, "Defocus disk u:    %f %f %f\n", c.defocus_disk_u.x, c.defocus_disk_u.y, c.defocus_disk_u.z);
  fprintf (stderr, "Defocus disk v:    %f %f %f\n", c.defocus_disk_v.x, c.defocus_disk_v.y, c.defocus_disk_v.z);
  fprintf (stderr, "Look from:         %f %f %f\n", c.lookfrom.x, c.lookfrom.y, c.lookfrom.z);
  fprintf (stderr, "Look at:           %f %f %f\n", c.lookat.x, c.lookat.y, c.lookat.z);
  fprintf (stderr, "Pixel origin:      %f %f %f\n", c.pixel_origin.x, c.pixel_origin.y, c.pixel_origin.z);
  fprintf (stderr, "Pixel delta u:     %f %f %f\n", c.pixel_delta_u.x, c.pixel_delta_u.y, c.pixel_delta_u.z);
  fprintf (stderr, "Pixel delta v:     %f %f %f\n", c.pixel_delta_v.x, c.pixel_delta_v.y, c.pixel_delta_v.z);
}

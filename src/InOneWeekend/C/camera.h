#pragma once

#include "point.h"

typedef struct camera
{
  double aspect_ratio;
  int    image_width;
  int    image_height;
  double vfov;
  double viewport_width;
  double viewport_height;
  point3 viewport_upper_left;
  vec3   pixel_delta_u;
  vec3   pixel_delta_v;
  point3 pixel_origin;
  int    samples_per_pixel;
  double pixel_samples_scale;
  int    max_depth;
  point3 lookfrom;
  point3 lookat;
  vec3   vup;
  vec3   u, v, w;
  double defocus_angle;  // Variation angle of rays through each pixel
  double focus_dist;     // Distance from camera lookfrom point to plane of perfect focus
  vec3   defocus_disk_u; // Defocus disk horizontal radius
  vec3   defocus_disk_v; // Defocus disk vertical radius
} camera;

extern camera cam;

struct hittable;
void camera_init (void);
void render (camera c, struct hittable **world);

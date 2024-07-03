#pragma once

#include "point.h"

typedef struct camera
{
  vec3_t pixel_delta_u;
  vec3_t pixel_delta_v;
  point3 pixel_origin;
  int    samples_per_pixel;
  int    max_depth;
  point3 lookfrom;
  point3 lookat;
  double focus_dist;     // Distance from camera lookfrom point to plane of perfect focus
  double defocus_angle;  // Variation angle of rays through each pixel
  vec3_t defocus_disk_u; // Defocus disk horizontal radius
  vec3_t defocus_disk_v; // Defocus disk vertical radius
} camera_t;

// global camera
extern camera_t g_camera;

void camera_init (void);
void render ();

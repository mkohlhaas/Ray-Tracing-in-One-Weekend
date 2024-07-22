#pragma once

#include "math/point.h"
#include <stdio.h>

typedef struct camera
{
  vec3_t   pixel_delta_u;
  vec3_t   pixel_delta_v;
  point3_t pixel_origin;
  int      samples_per_pixel;
  int      max_depth;
  point3_t lookfrom;
  point3_t lookat;
  double   focus_dist;     // Distance from camera lookfrom point to plane of perfect focus
  double   defocus_angle;  // Variation angle of rays through each pixel
  vec3_t   defocus_disk_u; // Defocus disk horizontal radius
  vec3_t   defocus_disk_v; // Defocus disk vertical radius
} camera_t;

void camera_init (void);
void render (FILE *output_file);

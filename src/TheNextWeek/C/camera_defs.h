#pragma once

// Set these values appropriately.
#define SAMPLES_PER_PIXEL 100
#define MAX_DEPTH         50
#define DEFOCUS_ANGLE     0.6            /* defocus blur = depth of field */
#define FOCUS_DIST        10.0;          /* focus distance = focus length (in our model) */
#define VFOV              20;            /* vertical field of view in degrees (edge to edge) */
#define VUP               up;            /* view up */
#define LOOKAT            origin         /* look at vector */
#define LOOKFROM                                                                                                       \
  (point3_t) { .x = 0, .y = 0, .z = 12 } /* eye/camera */

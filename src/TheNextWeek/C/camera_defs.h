#pragma once

// Set these values appropriately.
#define SAMPLES_PER_PIXEL 100
#define MAX_DEPTH         50
#define DEFOCUS_ANGLE     0.8            /* defocus blur = depth of field */
#define FOCUS_DIST        20.0;          /* focus distance = focus length (in our model) */
#define VFOV              35;            /* vertical field of view in degrees (edge to edge) */
#define VUP               up;            /* view up */
#define LOOKAT            origin         /* look at vector */
#define LOOKFROM                                                                                                       \
  (point3_t) { .x = 23, .y = 4, .z = 3 } /* eye/camera */

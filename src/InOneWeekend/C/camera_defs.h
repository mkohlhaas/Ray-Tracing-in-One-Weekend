// Set these values appropriately.
#define IMAGE_WIDTH       160 * 1
#define IMAGE_HEIGHT      90 * 1
#define SAMPLES_PER_PIXEL 100
#define MAX_DEPTH         50
#define DEFOCUS_ANGLE     0.6
#define FOCUS_DIST        10.0;
#define VFOV              20;
#define VUP               up;
#define ASPECT_RATIO      ((double)(IMAGE_WIDTH) / (IMAGE_HEIGHT))
#define LOOKAT            origin
#define LOOKFROM                                                                                                       \
  (point3) { .x = 13, .y = 2, .z = 3 }

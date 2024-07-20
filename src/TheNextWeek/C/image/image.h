#pragma once

typedef struct image
{
  int            bytes_per_pixel;    // bytes per pixel (normally i3)
  int            bytes_per_scanline; // bytes per scnaline
  float         *fdata;              // Linear floating point pixel data
  unsigned char *bdata;              // Linear 8-bit pixel data
  int            width;              // Loaded image width
  int            height;             // Loaded image height
} image_t;

image_t *image_from_file (char const *image_filename);
void     image_del (image_t *img);
int      image_height (image_t *img);
int      image_width (image_t *img);

unsigned char const *image_pixel_data (image_t *img, int x, int y);

#pragma once

#include <argp.h>

typedef struct arguments
{
  char *output_file;
  int   image_width;
  int   image_height;
  int   begin_scanline;
  int   num_scanlines;
} arguments_t;

extern struct argp argp;
extern arguments_t args;

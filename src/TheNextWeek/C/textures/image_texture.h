#pragma once

#include "image.h"
#include "texture.h"

typedef struct image_texture
{
  value_fn value;
  image_t *image;
} image_texture_t;

image_texture_t *image_texture_from_file (const char *filename);

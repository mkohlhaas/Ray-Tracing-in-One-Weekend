#include "image_texture.h"
#include "color.h"
#include "error.h"
#include "image.h"
#include "interval.h"
#include "texture.h"
#include <stdlib.h>

static color_t
value (texture_t *tex, double u, double v, point3_t const *p)
{
  (void)p;

  auto it = (image_texture_t *)tex;

  // If we have no texture data, then return solid cyan as a debugging aid.
  auto cyan = (color_t){
    .r = 0,
    .g = 1,
    .b = 1,
  };

  if (it->image->height <= 0)
    {
      return cyan;
    }

  // clamp input texture coordinates to [0,1] x [1,0]
  u = intvl_clamp ((interval_t){ 0, 1 }, u);
  v = 1.0 - intvl_clamp ((interval_t){ 0, 1 }, v); // flip v to image coordinates

  auto i  = u * it->image->width;
  auto j  = v * it->image->height;
  auto px = image_pixel_data (it->image, i, j);

  auto color_scale = 1.0 / 255.0;
  return (color_t){
    .r = color_scale * px[0],
    .g = color_scale * px[1],
    .b = color_scale * px[2],
  };
}

image_texture_t *
image_texture_from_file (const char *filename)
{
  image_texture_t *it = malloc (sizeof *it);
  if (!it)
    {
      logExit ("Out of memory");
    }
  it->value = value;
  it->image = image_from_file (filename);
  return it;
}

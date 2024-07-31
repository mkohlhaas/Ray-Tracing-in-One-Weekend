#include "math/color.h"
#include "math/interval.h"
#include "utils/utils.h"

void
color_write (FILE *out, color_t const pixel)
{
  interval_t intensity = { 0.000, 0.999 };

  // Apply a linear to gamma transform for gamma 2
  double r = linear_to_gamma (pixel.x);
  double g = linear_to_gamma (pixel.y);
  double b = linear_to_gamma (pixel.z);

  int red   = (int)(256 * intvl_clamp (intensity, r));
  int green = (int)(256 * intvl_clamp (intensity, g));
  int blue  = (int)(256 * intvl_clamp (intensity, b));

  // Write out the pixel color components.
  fprintf (out, "%d %d %d\n", red, green, blue);
}

// constant colors
color_t blue       = { .r = 0.0, .g = 0.0, .b = 1.0 };
color_t light_blue = { .r = 0.5, .g = 0.7, .b = 1.0 };
color_t red        = { .r = 1.0, .g = 0.0, .b = 0.0 };
color_t yellow     = { .r = 1.0, .g = 1.0, .b = 0.0 };
color_t white      = { .r = 1.0, .g = 1.0, .b = 1.0 };
color_t black      = { .r = 0.0, .g = 0.0, .b = 0.0 };
color_t grey       = { .r = 1.0, .g = 1.0, .b = 1.0 };
color_t light_grey = { .r = 0.3, .g = 0.3, .b = 0.3 };

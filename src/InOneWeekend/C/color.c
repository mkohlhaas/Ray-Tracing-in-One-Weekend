#include "color.h"
#include "interval.h"

void
write_color (FILE *out, color const pixel)
{
  interval intensity = { 0.000, 0.999 };
  int      red       = (int)(256 * clamp (intensity, pixel.r));
  int      green     = (int)(256 * clamp (intensity, pixel.g));
  int      blue      = (int)(256 * clamp (intensity, pixel.b));

  // Write out the pixel color components.
  fprintf (out, "%d %d %d\n", red, green, blue);
}

color blue  = { .r = 0.0, .g = 0.0, .b = 1.0 };
color red   = { .r = 1.0, .g = 0.0, .b = 0.0 };
color white = { .r = 1.0, .g = 1.0, .b = 1.0 };
color black = { .r = 0.0, .g = 0.0, .b = 0.0 };

#include "color.h"

void
write_color (FILE *out, color const pixel)
{
  // Translate the [0,1] component values to the byte range [0,255].
  int red   = (int)(255.999 * pixel.r);
  int green = (int)(255.999 * pixel.g);
  int blue  = (int)(255.999 * pixel.b);

  // Write out the pixel color components.
  fprintf (out, "%d %d %d\n", red, green, blue);
}

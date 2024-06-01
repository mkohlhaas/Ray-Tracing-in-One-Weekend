#include "color.h"
#include <stdio.h>

int
main (void)
{
  // image
  const int image_width  = 1024;
  const int image_height = 1024;

  // render
  printf ("P3\n%d %d\n255\n", image_width, image_height);

  // write image
  for (int row = 0; row < image_height; row++)
    {
      fprintf (stderr, "\rScanlines remaining: %d", image_height - row);
      for (int col = 0; col < image_width; col++)
        {
          color pixel = {
            .r = (double)row / (image_width - 1),
            .g = (double)col / (image_height - 1),
            .b = 0,
          };
          write_color (stdout, pixel);
        }
    }
  fprintf (stderr, "\rDone.                                   \n");
}

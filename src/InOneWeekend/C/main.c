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
          double r = (double)col / (image_width - 1);
          double g = (double)row / (image_height - 1);
          double b = 0.0;

          int ir = (int)(255.999999 * r);
          int ig = (int)(255.999999 * g);
          int ib = (int)(255.999999 * b);

          printf ("%d %d %d\n", ir, ig, ib);
        }
    }
  fprintf (stderr, "\rDone.                                   \n");
}

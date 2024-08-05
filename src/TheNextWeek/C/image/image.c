#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG

#include "image.h"
#include "error.h"
#include "stb_image.h"
#include <stdlib.h>

static unsigned char
float_to_byte (float value)
{
  if (value <= 0.0)
    {
      return 0;
    }
  else if (1.0 <= value)
    {
      return 255;
    }
  else
    {
      return 256 * value;
    }
}

// Convert the linear floating point pixel data to bytes, storing the resulting byte data in the `bdata` member.
static void
convert_to_bytes (image_t *img)
{
  int total_bytes = img->width * img->height * img->bytes_per_pixel;

  img->bdata = malloc (total_bytes);
  if (!img->bdata)
    {
      logExit ("Out of memory");
    }

  // Iterate through all pixel components, converting from [0.0, 1.0] float values to unsigned [0, 255] byte values.
  auto bptr = img->bdata;
  auto fptr = img->fdata;
  for (auto i = 0; i < total_bytes; i++, fptr++, bptr++)
    {
      *bptr = float_to_byte (*fptr);
    }
}

// Returns the value clamped to the range [`low`, `high`).
static int
clamp (int x, int low, int high)
{
  if (x < low)
    {
      return low;
    }
  else if (x < high)
    {
      return x;
    }
  else
    {
      return high - 1;
    }
}

// Return the address of the three RGB bytes of the pixel at `x`, `y`.
// If there is no image data, returns magenta (for debugging).
unsigned char const *
image_pixel_data (image_t *img, int x, int y)
{
  static unsigned char magenta[] = { 255, 0, 255 };
  if (!img->bdata)
    {
      return magenta;
    }

  x = clamp (x, 0, img->width);
  y = clamp (y, 0, img->height);

  return img->bdata + x * img->bytes_per_pixel + y * img->bytes_per_scanline;
}

void
image_del (image_t *img)
{
  free (img->bdata);
  STBI_FREE (img->fdata);
}

// Returns `0` if image not loaded.
int
image_height (image_t *img)
{
  return (img->fdata) ? img->height : 0;
}

// Returns `0` if image not loaded.
int
image_width (image_t *img)
{
  return (img->fdata) ? img->width : 0;
}

// Loads the linear (gamma=1) image data from `filename`. Returns `true` if the
// load succeeded. The resulting data buffer contains the three [0.0, 1.0]
// floating-point values for the first pixel (red, then green, then blue). Pixels are
// contiguous, going left to right for the width of the image, followed by the next row
// below, for the full height of the image.
static bool
image_load (image_t *img, char const *filename)
{
  auto n     = img->bytes_per_pixel; // unused dummy parameter
  img->fdata = stbi_loadf (filename, &img->width, &img->height, &n, img->bytes_per_pixel);
  if (!img->fdata)
    {
      return false;
    }

  img->bytes_per_scanline = img->width * img->bytes_per_pixel;
  convert_to_bytes (img);
  return true;
}

// Loads image data from the specified file. If the `RAYTRACER_IMAGES` environment variable is
// defined, looks only in that directory for the image file.
// Returns `NULL` if image could not be loaded.
image_t *
image_from_file (char const *image_filename)
{
  image_t *img = malloc (sizeof *img);
  if (!img)
    {
      logError ("Could not allocate memory for image file: %s", image_filename);
      return NULL;
    }

  img->bytes_per_pixel    = 3;
  img->fdata              = NULL; // Linear floating point pixel data
  img->bdata              = NULL; // Linear 8-bit pixel data
  img->width              = 0;    // Loaded image width
  img->height             = 0;    // Loaded image height
  img->bytes_per_scanline = 0;

  // build full path name
  char image_path_name[1024];
  auto imagedir = getenv ("RAYTRACER_IMAGES");

  if (imagedir)
    {
      snprintf (image_path_name, sizeof image_path_name, "%s%s%s", imagedir, "/", image_filename);
    }
  else
    {
      snprintf (image_path_name, sizeof image_path_name, "%s", image_filename);
    }

  // load image
  if (!image_load (img, image_path_name))
    {
      logError ("Could not load image file: %s", image_path_name);
      return NULL;
    }

  return img;
}

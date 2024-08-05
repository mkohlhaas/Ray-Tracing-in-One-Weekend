#include "perlin_smooth.h"
#include "error.h"
#include "utils.h"
#include <math.h>

static void
shuffle (int p[], int n)
{
  for (int i = n - 1; i > 0; i--)
    {
      int target = random_int_min_max (0, i);
      int tmp    = p[i];
      p[i]       = p[target];
      p[target]  = tmp;
    }
}

static int *
perlin_generate_perm (perlin_smooth_t *p)
{
  int *perm = malloc (sizeof (int) * p->point_count);
  if (!perm)
    {
      logExit ("Out of memory");
    }

  for (int i = 0; i < p->point_count; i++)
    {
      perm[i] = i;
    }

  shuffle (perm, p->point_count);

  return perm;
}

perlin_smooth_t *
perlin_smooth_new ()
{
  perlin_smooth_t *p = malloc (sizeof *p);
  if (!p)
    {
      logExit ("Out of memory");
    }

  p->point_count = 256;
  p->randfloat   = malloc (sizeof (*p->randfloat) * p->point_count);
  for (int i = 0; i < p->point_count; i++)
    {
      p->randfloat[i] = random_double ();
    }

  p->perm_x = perlin_generate_perm (p);
  p->perm_y = perlin_generate_perm (p);
  p->perm_z = perlin_generate_perm (p);
  return p;
}

void
perlin_smooth_del (perlin_smooth_t *p)
{
  free (p->randfloat);
  free (p->perm_x);
  free (p->perm_y);
  free (p->perm_z);
}

static double
trilinear_interp (double c[2][2][2], double u, double v, double w)
{
  auto accum = 0.0;
  for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 2; j++)
        {
          for (int k = 0; k < 2; k++)
            {
              accum += (i * u + (1 - i) * (1 - u)) * (j * v + (1 - j) * (1 - v)) * (k * w + (1 - k) * (1 - w))
                       * c[i][j][k];
            }
        }
    }

  return accum;
}

double
perlin_smooth_noise (perlin_smooth_t *p, const point3_t *point)
{
  auto u = point->x - floor (point->x);
  auto v = point->y - floor (point->y);
  auto w = point->z - floor (point->z);

  auto i = (int)(floor (point->x));
  auto j = (int)(floor (point->y));
  auto k = (int)(floor (point->z));

  double c[2][2][2];
  for (int di = 0; di < 2; di++)
    {
      for (int dj = 0; dj < 2; dj++)
        {
          for (int dk = 0; dk < 2; dk++)
            {
              c[di][dj][dk]
                  = p->randfloat[p->perm_x[(i + di) & 255] ^ p->perm_y[(j + dj) & 255] ^ p->perm_z[(k + dk) & 255]];
            }
        }
    }

  return trilinear_interp (c, u, v, w);
}

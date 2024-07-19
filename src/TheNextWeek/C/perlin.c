#include "perlin.h"
#include "error.h"
#include "point.h"
#include "utils.h"
#include <stdlib.h>

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
perlin_generate_perm (perlin_t *p)
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

perlin_t *
perlin_new ()
{
  perlin_t *p = malloc (sizeof *p);
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
perlin_del (perlin_t *p)
{
  free (p->randfloat);
  free (p->perm_x);
  free (p->perm_y);
  free (p->perm_z);
}

double
perlin_noise (perlin_t *p, const point3_t *point, int granularity)
{
  auto i = (int)(granularity * point->x) & 255;
  auto j = (int)(granularity * point->y) & 255;
  auto k = (int)(granularity * point->z) & 255;

  return p->randfloat[p->perm_x[i] ^ p->perm_y[j] ^ p->perm_z[k]];
}

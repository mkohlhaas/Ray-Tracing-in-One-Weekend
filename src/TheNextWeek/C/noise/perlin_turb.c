#include "perlin_turb.h"
#include "error.h"
#include "point.h"
#include "utils.h"
#include "vec3.h"
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
perlin_generate_perm (perlin_turb_t *p)
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

perlin_turb_t *
perlin_turb_new ()
{
  perlin_turb_t *p = malloc (sizeof *p);
  if (!p)
    {
      logExit ("Out of memory");
    }

  p->point_count = 256;
  p->randvec     = malloc (sizeof (*p->randvec) * p->point_count);
  for (int i = 0; i < p->point_count; i++)
    {
      p->randvec[i] = vec3_unit (vec3_random_min_max (-1, 1));
    }

  p->perm_x = perlin_generate_perm (p);
  p->perm_y = perlin_generate_perm (p);
  p->perm_z = perlin_generate_perm (p);
  return p;
}

void
perlin_turb_del (perlin_turb_t *p)
{
  free (p->randvec);
  free (p->perm_x);
  free (p->perm_y);
  free (p->perm_z);
}

static double
perlin_interp (const vec3_t c[2][2][2], double u, double v, double w)
{
  auto uu    = u * u * (3 - 2 * u);
  auto vv    = v * v * (3 - 2 * v);
  auto ww    = w * w * (3 - 2 * w);
  auto accum = 0.0;

  for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 2; j++)
        {
          for (int k = 0; k < 2; k++)
            {
              auto weight_v = (vec3_t){ .x = u - i, .y = v - j, .z = w - k };
              accum += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) * (k * ww + (1 - k) * (1 - ww))
                       * vec3_dot (c[i][j][k], weight_v);
            }
        }
    }

  return accum;
}

static double
perlin_turb_noise (perlin_turb_t *p, const point3_t *point)
{
  auto u = point->x - floor (point->x);
  auto v = point->y - floor (point->y);
  auto w = point->z - floor (point->z);

  auto i = (int)(floor (point->x));
  auto j = (int)(floor (point->y));
  auto k = (int)(floor (point->z));

  vec3_t c[2][2][2];
  for (int di = 0; di < 2; di++)
    {
      for (int dj = 0; dj < 2; dj++)
        {
          for (int dk = 0; dk < 2; dk++)
            {
              c[di][dj][dk]
                  = p->randvec[p->perm_x[(i + di) & 255] ^ p->perm_y[(j + dj) & 255] ^ p->perm_z[(k + dk) & 255]];
            }
        }
    }

  return perlin_interp (c, u, v, w);
}

double
perlin_turb_turbulence (perlin_turb_t *p, point3_t const *point, int depth)
{
  auto     accum  = 0.0;
  point3_t temp_p = *point;
  auto     weight = 1.0;

  for (int i = 0; i < depth; i++)
    {
      accum += weight * perlin_turb_noise (p, &temp_p);
      weight *= 0.5;
      temp_p = vec3_mult (2, temp_p);
    }

  return fabs (accum);
}

#pragma once

#include <stdbool.h>

typedef struct interval
{
  double low;
  double high;
} interval_t;

extern interval_t const intvl_empty;
extern interval_t const intvl_universe;

double     intvl_size (interval_t intvl);
bool       intvl_contains (interval_t intvl, double x);
bool       intvl_surrounds (interval_t intvl, double x);
double     intvl_clamp (interval_t intvl, double x);
interval_t intvl_expand (interval_t intvl, double delta);
interval_t intvl_from_intvls (interval_t const a, interval_t const b);
interval_t intvl_add_displacement (interval_t const a, double displacement);

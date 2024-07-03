#pragma once

#include <stdbool.h>

typedef struct interval
{
  double min, max;
} interval_t;

extern interval_t empty;
extern interval_t universe;

double itvl_size (interval_t i);
bool   itvl_contains (interval_t i, double x);
bool   itvl_surrounds (interval_t i, double x);
double itvl_clamp (interval_t i, double x);

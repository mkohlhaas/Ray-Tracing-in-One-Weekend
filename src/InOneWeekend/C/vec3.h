#pragma once

typedef union vec3_union
{
  double element[3];
  struct
  {
    union
    {
      double x, r, s, u;
    };
    union
    {
      double y, g, t, v;
    };
    union
    {
      double z, b, p, w;
    };
  };
} vec3;

typedef vec3 point3;
typedef vec3 color;

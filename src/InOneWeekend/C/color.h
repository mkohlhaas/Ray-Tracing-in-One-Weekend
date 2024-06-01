#pragma once

#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

void write_color (FILE *out, const color pixel_color);

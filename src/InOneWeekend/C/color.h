#pragma once

#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

extern color blue;
extern color light_blue;
extern color red;
extern color white;
extern color black;
extern color yellow;

void write_color (FILE *out, const color pixel_color);

#pragma once

#include "point.h"
#include "ray.h"
#include <stdbool.h>

bool hit_sphere (point3 const center, double radius, ray const r);

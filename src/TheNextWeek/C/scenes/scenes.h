#pragma once

#include "error/error.h"

#define CHECK_MEMORY                                                                                                   \
  if (!m || !s)                                                                                                        \
    {                                                                                                                  \
      logExit ("Out of memory");                                                                                       \
    }

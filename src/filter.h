#include <math.h>
#include "./filterconfig.h"
#include <stdbool.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#endif

#ifndef FILTER
#define FILTER

bool greater(uint8_t *p, filterconfig_t cfg);
bool less(uint8_t *p, filterconfig_t cfg);
bool equal(uint8_t *p, filterconfig_t cfg);
bool greater_equal(uint8_t *p, filterconfig_t cfg);
bool less_equal(uint8_t *p, filterconfig_t cfg);
bool between(uint8_t *p, filterconfig_t cfg);
bool outside(uint8_t *p, filterconfig_t cfg);

#endif

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#endif

#include <math.h>

// Bitwise
uint8_t and_fx(uint8_t *p, int value);
uint8_t or_fx(uint8_t *p, int value);
uint8_t xor_fx(uint8_t *p, int value);

// Arithmetic
uint8_t add_fx(uint8_t *p, int value);
uint8_t sub_fx(uint8_t *p, int value);
uint8_t mul_fx(uint8_t *p, int value);
uint8_t div_fx(uint8_t *p, int value);
uint8_t mod_fx(uint8_t *p, int value);
uint8_t pow_fx(uint8_t *p, int value);
uint8_t root_fx(uint8_t *p);
uint8_t log_fx(uint8_t *p);

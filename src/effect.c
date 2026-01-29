#include "./effect.h"

// Bitwise
uint8_t and_fx(uint8_t *p, int value) {
	return (uint8_t)(*p & value);
}
uint8_t or_fx(uint8_t *p, int value) {
	return (uint8_t)(*p | value);
}
uint8_t xor_fx(uint8_t *p, int value) {
	return (uint8_t)(*p ^ value);
}

// Arithmetic
uint8_t add_fx(uint8_t *p, int value) {
	return (uint8_t)(*p + value);
}

uint8_t sub_fx(uint8_t *p, int value) {
	return (uint8_t)(*p - value);
}

uint8_t mul_fx(uint8_t *p, int value) {
	return (uint8_t)(*p * value);
}

uint8_t div_fx(uint8_t *p, int value) {
	if (value == 0) {
		return (uint8_t)0;
	}
	return (uint8_t)(*p / value);
}

uint8_t mod_fx(uint8_t *p, int value) {
	return (uint8_t) (*p % value);
}

uint8_t pow_fx(uint8_t *p, int value) {
	return (uint8_t) pow(*p, value);
}

uint8_t root_fx(uint8_t *p) {
	return (uint8_t) sqrt(*p);
}

uint8_t log_fx(uint8_t *p) {
	return (uint8_t) log(*p);
}

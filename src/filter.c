#include "./filter.h"

bool greater(uint8_t *p, filterconfig_t cfg) {
	return (*p > cfg.value);
}

bool less(uint8_t *p, filterconfig_t cfg) {
	return (*p < cfg.value);
}

bool equal(uint8_t *p, filterconfig_t cfg) {
		return (*p == cfg.value);
}

bool greater_equal(uint8_t *p, filterconfig_t cfg) {
		return (*p >= cfg.value);
}

bool less_equal(uint8_t *p, filterconfig_t cfg) {
		return (*p <= cfg.value);
}

bool between(uint8_t *p, filterconfig_t cfg) {
	return (*p > cfg.min && *p < cfg.max);
}

bool outside(uint8_t *p, filterconfig_t cfg) {
		return (*p < cfg.min || *p > cfg.max);
}

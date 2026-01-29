#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#endif
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image_write.h"
#endif

#include "./filterconfig.h"
#include "./effect.c"
#include "./filter.c"

/* type definition for a function which compares two pixels and returns a bool
	 where uint8_t is the pixel, and filterconfig_t is the data that the filter function needs
 */
typedef bool (*filterfn_t)(uint8_t*, filterconfig_t);
typedef uint8_t (*effectfn_t)(uint8_t*, int);

/** Apply an effect to a single pixel */
uint8_t apply(uint8_t *p, effectfn_t effect, int effect_value, filterfn_t filter, filterconfig_t filter_config) {
	if (filter(p, filter_config)) {
		return effect(p, effect_value);
	}
	return *p;
}

unsigned char* and(unsigned char* img, int width, int height, int channels, int r, int g, int b) {
	size_t img_size = width * height * channels;
	unsigned char *out_img = malloc(img_size);
	if (out_img == NULL) {
		printf("Unable to allocate memory for output image\n");
		exit(1);
	}

	for (unsigned char *p = img, *po = out_img; p != img + img_size; p += channels, po += channels) {
		*po = apply(p, and_fx, r, between, (filterconfig_t){0, 200, 255});
    *(po + 1) = apply((p + 1), and_fx, g, less, (filterconfig_t){255, -1, -1});
    *(po + 2) = apply((p + 2), and_fx, b, less, (filterconfig_t){255, -1, -1});
	}

	return out_img;
}

unsigned char* cutoff(unsigned char* img, int width, int height, int channels, filterconfig_t r_cfg, filterconfig_t g_cfg, filterconfig_t b_cfg) {
	size_t img_size = width * height * channels;
	unsigned char *out_img = malloc(img_size);
	if (out_img == NULL) {
		printf("Unable to allocate memory for output image\n");
		exit(1);
	}

	for (unsigned char *p = img, *po = out_img; p != img + img_size; p += channels, po += channels) {
		*po = apply(p, xor_fx, *p, outside, r_cfg);
    *(po + 1) = apply((p + 1), xor_fx, *(p + 1), outside, g_cfg);
    *(po + 2) = apply((p + 2), xor_fx, *(p + 2), outside, b_cfg);
	}

	return out_img;
}

unsigned char* grayscale(unsigned char *img, int width, int height, int channels) {
	size_t img_size = width * height * channels;
	int gray_channels = channels == 4 ? 2 : 1;
	size_t gray_img_size = width * height * gray_channels;

	unsigned char *gray_img = malloc(gray_img_size);
	if (gray_img == NULL) {
		printf("Unable to allocate memory for gray image\n");
		exit(1);
	}

	for (unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) {
		*pg = (uint8_t) ((*p + *(p + 1) + *(p + 2)) / 3.0);
		if (channels == 4) {
			*(pg + 1) = *(pg + 3);
		}
	}

	return gray_img;
}


unsigned char* or(unsigned char* img, int width, int height, int channels, int r, int g, int b) {
	size_t img_size = width * height * channels;
	unsigned char *out_img = malloc(img_size);
	if (out_img == NULL) {
		printf("Unable to allocate memory for output image\n");
		exit(1);
	}

	for (unsigned char *p = img, *po = out_img; p != img + img_size; p += channels, po += channels) {
		*po = (uint8_t) (*p | r);
		*(po + 1) = (uint8_t) ((*p + 1) | g);
		*(po + 2) = (uint8_t) ((*p + 2) | b);
	}

	return out_img;
}

unsigned char* xor(unsigned char* img, int width, int height, int channels, int r, int g, int b) {
	size_t img_size = width * height * channels;
	unsigned char *out_img = malloc(img_size);
	if (out_img == NULL) {
		printf("Unable to allocate memory for output image\n");
		exit(1);
	}

	for (unsigned char *p = img, *po = out_img; p != img + img_size; p += channels, po += channels) {
		*po = (uint8_t) (*p ^ r);
		*(po + 1) = (uint8_t) ((*p ^ 1) | g);
		*(po + 2) = (uint8_t) ((*p ^ 2) | b);
	}

	return out_img;
}


int main(void) {
	int width, height, channels;
	unsigned char *img = stbi_load("../images/test.jpg", &width, &height, &channels, 0);
	if (img == NULL) {
		printf("Error loading image\n");
		exit(1);
	}
	printf("Loaded image with dimensions %d x %d and %d channels\n", width, height, channels);


	unsigned char *gray_img = grayscale(img, width, height, channels);
	unsigned char *red_and_img = and(img, width, height, channels, 255, 0, 0);
	unsigned char *green_and_img = and(img, width, height, channels, 0, 255, 0);
	unsigned char *blue_and_img = and(img, width, height, channels, 0, 0, 255);
	unsigned char *cutoff_img = cutoff(img, width, height, channels, (filterconfig_t){0, 100, 255}, (filterconfig_t){0, 100, 255}, (filterconfig_t){0, 0, 0});
	
	stbi_write_jpg("test_red.jpg", width, height, channels, red_and_img, 100);
	stbi_write_jpg("test_blue.jpg", width, height, channels, green_and_img, 100);
	stbi_write_jpg("test_green.jpg", width, height, channels, blue_and_img, 100);
	stbi_write_jpg("test_cutoff.jpg", width, height, channels, cutoff_img, 100);
	
	stbi_image_free(red_and_img);
	stbi_image_free(green_and_img);
	stbi_image_free(blue_and_img);
	stbi_image_free(gray_img);
	stbi_image_free(cutoff_img);
	stbi_image_free(img); // Free the memory
	
	return 0;
}

/**
	 (load-image :path "image.jpg" :var image)
	 (defilter red-greater-than-blue
	 (less R B))
	 (xor :image image :where red-greater-than-blue) ;; runs the xor C function
	 (save-image :path "out.jpg" :image image)
**/

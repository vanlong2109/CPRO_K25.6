#include "led_driver.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* Internal static data for the LED driver */
static uint32_t *g_led_buffer = NULL;
static size_t g_led_pixel_count = 0;

int led_init(size_t num_pixels)
{
    /* Validate input */
    if (num_pixels == 0) {
        return -1;
    }

    /* If already initialized, free and re-init with new size */
    if (g_led_buffer != NULL) {
        free(g_led_buffer);
        g_led_buffer = NULL;
        g_led_pixel_count = 0;
    }

    /* Allocate and zero-initialize buffer */
    g_led_buffer = (uint32_t *)calloc(num_pixels, sizeof(uint32_t));
    if (g_led_buffer == NULL) {
        return -1;
    }
    g_led_pixel_count = num_pixels;
    return 0;
}

void led_shutdown()
{
    if (g_led_buffer != NULL) {
        free(g_led_buffer);
        g_led_buffer = NULL;
    }
    g_led_pixel_count = 0;
}

void led_set_color(size_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    /* Check range */
    if (g_led_buffer == NULL || index >= g_led_pixel_count) {
        return; /* silently ignore invalid indexes */
    }

    /* Pack into 32-bit value in GRB order: [00][G][R][B] */
    uint32_t color = (((uint32_t)green) << 16) | (((uint32_t)red) << 8) | ((uint32_t)blue);
    g_led_buffer[index] = color;
}

void led_fill(uint8_t red, uint8_t green, uint8_t blue)
{
    if (g_led_buffer == NULL || g_led_pixel_count == 0) {
        return;
    }
    uint32_t color = (((uint32_t)green) << 16) | (((uint32_t)red) << 8) | ((uint32_t)blue);
    for (size_t i = 0; i < g_led_pixel_count; ++i) {
        g_led_buffer[i] = color;
    }
}

void led_clear()
{
    led_fill(0, 0, 0);
}

const uint32_t* led_get_buffer()
{
    return (const uint32_t*)g_led_buffer;
}

size_t led_get_pixel_count()
{
    return g_led_pixel_count;
}

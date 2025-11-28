/* Header for LED driver: simple API used by the test main.
 * Implements a GRB-packed 24-bit color stored in a 32-bit value.
 */
#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int led_init(size_t num_pixels);
void led_shutdown(void);
void led_set_color(size_t index, uint8_t red, uint8_t green, uint8_t blue);
void led_fill(uint8_t red, uint8_t green, uint8_t blue);
void led_clear(void);
const uint32_t* led_get_buffer(void);
size_t led_get_pixel_count(void);

#endif /* LED_DRIVER_H */
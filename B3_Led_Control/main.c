#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "led_driver.h"

int main(void)
{
    const size_t NUM_PIXELS = 10;
    if (led_init(NUM_PIXELS) != 0) {
        fprintf(stderr, "led_init failed\n");
        return EXIT_FAILURE;
    }

    const uint32_t *buf = led_get_buffer();
    size_t count = led_get_pixel_count();
    if (buf == NULL || count != NUM_PIXELS) {
        fprintf(stderr, "Initialization error: buffer null or wrong count (%zu)\n", count);
        led_shutdown();
        return EXIT_FAILURE;
    }

    /* Check buffer is zero-initialized */
    for (size_t i = 0; i < count; ++i) {
        if (buf[i] != 0) {
            fprintf(stderr, "Buffer not zero-initialized at index %zu: 0x%08" PRIX32 "\n", i, buf[i]);
            led_shutdown();
            return EXIT_FAILURE;
        }
    }

    /* Set some pixels as described */
    led_set_color(0, 255, 0, 0);   /* Red */
    led_set_color(9, 0, 0, 255);   /* Blue */
    led_set_color(4, 255, 255, 255); /* White */

    /* Re-grab buffer pointer in case led_set_color updated it */
    buf = led_get_buffer();

    printf("Index 0: 0x%08" PRIX32 " (expected 0x0000FF00 = Red)\n", buf[0]);
    printf("Index 4: 0x%08" PRIX32 " (expected 0x00FFFFFF = White)\n", buf[4]);
    printf("Index 9: 0x%08" PRIX32 " (expected 0x000000FF = Blue)\n", buf[9]);

    /* Verify expected values programmatically */
    const uint32_t expected_red = ((uint32_t)255 << 8);
    const uint32_t expected_blue = ((uint32_t)255);
    const uint32_t expected_white = (((uint32_t)255 << 16) | ((uint32_t)255 << 8) | (uint32_t)255);

    if (buf[0] != expected_red) {
        fprintf(stderr, "FAIL: Index 0 expected 0x%08" PRIX32 ", got 0x%08" PRIX32 "\n", expected_red, buf[0]);
        led_shutdown();
        return EXIT_FAILURE;
    }
    if (buf[4] != expected_white) {
        fprintf(stderr, "FAIL: Index 4 expected 0x%08" PRIX32 ", got 0x%08" PRIX32 "\n", expected_white, buf[4]);
        led_shutdown();
        return EXIT_FAILURE;
    }
    if (buf[9] != expected_blue) {
        fprintf(stderr, "FAIL: Index 9 expected 0x%08" PRIX32 ", got 0x%08" PRIX32 "\n", expected_blue, buf[9]);
        led_shutdown();
        return EXIT_FAILURE;
    }

    printf("Basic color checks passed.\n");

    /* Fill with Green (0,255,0) and verify */
    led_fill(0, 255, 0);
    buf = led_get_buffer();
    const uint32_t expected_green = ((uint32_t)255 << 16);
    for (size_t i = 0; i < count; ++i) {
        if (buf[i] != expected_green) {
            fprintf(stderr, "FAIL: After fill, index %zu expected 0x%08" PRIX32 ", got 0x%08" PRIX32 "\n", i, expected_green, buf[i]);
            led_shutdown();
            return EXIT_FAILURE;
        }
    }
    printf("Fill with green check passed (0x%08" PRIX32 ").\n", expected_green);

    led_shutdown();
    if (led_get_buffer() != NULL || led_get_pixel_count() != 0) {
        fprintf(stderr, "WARNING: shutdown did not clear state properly\n");
    }

    printf("All tests passed.\n");
    return EXIT_SUCCESS;
}
/* End of tests */
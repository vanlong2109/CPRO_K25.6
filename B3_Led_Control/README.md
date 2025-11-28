# B3 LED Control (Demo & Test)

This folder contains a simple LED driver (`led_driver.c`) and a demo/test program (`main.c`) used to validate buffer allocation, GRB color packing, and utility operations (fill/clear).

Build
-----
You can build the demo using the provided Makefile (requires `gcc`):

```bash
cd B3_Led_Control
make
```

Run tests
---------
To run the test program:

```bash
make test
```

Expected output
---------------
The demo will print values for pixel indices 0, 4 and 9 and confirm the values match the expected GRB-packed values.
```
Index 0: 0x0000FF00 (expected 0x0000FF00 = Red)
Index 4: 0x00FFFFFF (expected 0x00FFFFFF = White)
Index 9: 0x000000FF (expected 0x000000FF = Blue)
Basic color checks passed.
Fill with green check passed (0x00FF0000).
All tests passed.
```

Color format
------------
This driver uses a 24-bit GRB format packed into a 32-bit integer:

- Bits [23:16] = Green
- Bits [15:8] = Red
- Bits [7:0] = Blue

Examples:
- Red: 0x0000FF00
- Green: 0x00FF0000
- Blue: 0x000000FF
- White: 0x00FFFFFF

Notes
-----
- The driver exposes a minimal API included in `led_driver.h`.
- `led_init()` allocates and zero-initializes the pixel buffer; `led_shutdown()` frees it.
- The demo asserts that writes and fills behave as expected.

License & Author
----------------
Add your license and author info here as needed.

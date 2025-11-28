CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -I.
TARGET := led_test
SRCS := led_driver.c main.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJS)

test: all
	./$(TARGET)

.PHONY: all clean test

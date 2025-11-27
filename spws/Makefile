PROJECT_DIR := spws
CC          := gcc
CFLAGS      := -Wall -Wextra -std=c11
INCLUDE     := -I$(PROJECT_DIR) -I$(PROJECT_DIR)/hal_library -I$(PROJECT_DIR)/spws_controller
TARGET      := $(PROJECT_DIR)/spws

SRCS := $(PROJECT_DIR)/main.c \
        $(PROJECT_DIR)/spws_controller/spws_controller.c \
        $(PROJECT_DIR)/hal_library/hal_actuators.c \
        $(PROJECT_DIR)/hal_library/hal_buttons.c \
        $(PROJECT_DIR)/hal_library/hal_sensors.c

OBJS := $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(PROJECT_DIR)/%.o: $(PROJECT_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

CC := gcc
CFLAGS := -Wall -Wextra -O2
INCLUDES := -I./vendor/raylib/src
LIBS := -lGL -lm
SRC := main.c
TARGET := main
RAYLIB := ./vendor/raylib/src/libraylib.a

.PHONY := all clean

all: $(TARGET)

$(TARGET): $(SRC) $(RAYLIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(RAYLIB) $(LIBS) -o $@

clean:
	rm -f $(TARGET)

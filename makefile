CC = gcc
CFLAGS := -std=c11 -Iinclude $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_image)
LDLIBS := -lm $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image)

TARGET :=
ifeq ($(OS),Windows_NT)
	TARGET+=shooter.exe
else
	TARGET+=shooter
endif

BINDIR = bin

$(TARGET):
	$(CC) $(CFLAGS) src/main.c -o $(BINDIR)/$@ $(LDLIBS)

setup:
	mkdir -p $(BINDIR)

clean:
	rm $(BINDIR)/$(TARGET)

CC = gcc
CFLAGS := -std=c11 $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_image)
LDLIBS := -lm $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image)

TARGET :=
ifeq ($(OS),Windows_NT)
	TARGET+=test.exe
else
	TARGET+=test
endif

BINDIR = bin

$(TARGET):
	$(CC) $(CFLAGS) src/test.c -o $(BINDIR)/$@ $(LDLIBS)

setup:
	mkdir -p $(BINDIR)

clean:
	rm $(BINDIR)/$(TARGET)

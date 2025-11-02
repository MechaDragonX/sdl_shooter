CC = gcc
CFLAGS := -std=c11 -Iinclude $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_image)
LDLIBS := -lm $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image)

OBJS=obj/entity.o obj/main.o

TARGET :=
ifeq ($(OS),Windows_NT)
	TARGET += shooter.exe
else
	TARGET += shooter
endif

OBJDIR = obj
BINDIR = bin

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/$@ $(LDLIBS)

obj/entity.o: src/entity.c include/entity.h
	$(CC) $(CFLAGS) $< -c -o $@

obj/main.o: src/main.c include/entity.h
	$(CC) $(CFLAGS) $< -c -o $@

setup:
	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm $(OBJS) $(BINDIR)/$(TARGET)

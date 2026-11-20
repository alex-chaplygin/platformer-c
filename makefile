OBJS=main.o graphics.o image.o backend.o animation.o
LDFLAGS=-lSDL2 -lSDL2_image
CFLAGS=-g
TARGET = platformer

$(TARGET): $(OBJS)
	gcc $^ -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(DESTDIR)$(OBJS) $(DESTDIR)$(TARGET)

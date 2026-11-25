SRC=main.o graphics.o image.o backend.o animation.o generator.o
LDFLAGS=-lSDL2 -lSDL2_image
CFLAGS=-g

/tmp/platformer: $(SRC)
	gcc $^ -o $@ $(LDFLAGS)

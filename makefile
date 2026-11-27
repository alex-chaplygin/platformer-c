ENGINE=engine/graphics.o engine/image.o engine/backend.o engine/animation.o
SRC=$(ENGINE) generator.o main.o
LDFLAGS=-lSDL2 -lSDL2_image
CFLAGS=-g

/tmp/platformer: $(SRC)
	gcc $^ -o $@ $(LDFLAGS)

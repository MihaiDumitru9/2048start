TARGET = joc

SRCS = main.c render.c logic.c

all:
	gcc -o $(TARGET) $(SRCS) $(shell sdl2-config --cflags --libs) -lSDL2_ttf
	
	./$(TARGET)

clean:
	rm -f $(TARGET)

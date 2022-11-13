CC=g++
CFLAGS=-I. -I/usr/include/opencv4 `pkg-config opencv4 --cflags --libs` 
DEPS = sobel.h
OBJ = main.o sobel.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sobelFilter: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

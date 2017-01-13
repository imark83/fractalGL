# makefile para Canvas. version 0.1
# uso de variables; reglas predefinidas

CC = g++
# OBJECTS = coreLoop.o carreterometro.o
TARGETS = main.cpp loadShaders.cpp fractal.cpp
LIBS = -lGL -lGLEW -lglut
CFLAGS = -g -I include


.PHONY : all
all :
	$(CC) $(TARGETS) $(LIBS) $(CFLAGS) -o aaa

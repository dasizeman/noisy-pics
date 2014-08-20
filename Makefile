CC=gcc
TARGETS=sound
LINKS=-lm -lportaudio -lasound -lrt -lpthread `pkg-config --libs opencv`
FLAGS=`pkg-config --cflags opencv`

default:build

build:main

main: $(TARGETS)

$(TARGETS): src/*.c src/*.h
	$(CC) -o $@ $(FLAGS) $^ $(LINKS)


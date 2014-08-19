CC=gcc
TARGETS=sound
LINKS=-lm -lportaudio -lasound -lrt -lpthread

default:build

build:main

main: $(TARGETS)

$(TARGETS): src/*.c src/*.h
	$(CC) -o $@ $^ $(LINKS)


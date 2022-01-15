CC=gcc --std=gnu99 -g

all: image prng ui

image: image.c
	$(CC) image.c -o image

prng: prng.c
	$(CC) prng.c -o prng

ui: ui.c
	$(CC) ui.c -o ui

clean:
	rm -f image prng ui
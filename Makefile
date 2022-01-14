CC=gcc --std=gnu99 -g

all: image prng

image: image.c
	$(CC) image.c -o image

prng: prng.c
	$(CC) prng.c -o prng

clean:
	rm -f image prng
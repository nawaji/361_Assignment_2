/**************************************
 * ith image picker (Image Service)
 * tojo@oregonstate.edu
 * 1/12/22
 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int read_instructions() {
	char path[27] = "./image-service.txt";
	char buffer[6];

	FILE* readfile = fopen(path, "r");
	if (readfile != NULL && !feof(readfile)) {
		fgets(buffer, sizeof(buffer), readfile);
//		printf("buffer: %d\n", buffer);
		for (int i = 0; i < sizeof(buffer); i++) {
			printf("%c", buffer[i]);
		}

	} else {
		printf("image-service.txt or it's contents are missing.\n");
		return 0;
	}
}

void write_path() {
	srand(time(NULL));
	char path[27] = "./prng-service.txt";
	char to_write[6];

	int key = rand() % 99999;
	snprintf(to_write, sizeof(to_write), "%d", key);

	FILE* writefile = fopen(path, "w");
	if (writefile != NULL) {
		fputs(to_write, writefile);
		fclose(writefile);
	}
}

int main() {
	if (read_instructions() == 1) {
		write_path();
	}

	return 0;
}
/**************************************
 * Pseudo-random number gen (PRNG Service)
 * tojo@oregonstate.edu
 * 1/12/22
 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int read_instructions() {
	char path[27] = "./prng-service.txt";
	char buffer[10];

	FILE* readfile = fopen(path, "r");
	if (readfile != NULL && !feof(readfile)) {
		fgets(buffer, sizeof(buffer), readfile);
		for (int i = 0; i < sizeof(buffer); i++) {
			if (buffer[i] == '\n') {
				buffer[i] = '\0';
				break;
			}
		}
		if (strncmp("run", buffer, strlen(buffer)) == 0) {
			fclose(readfile);
			return 1;

		} else {
			printf("Please provide \"prng-service.txt\" containing");
			printf(" only the word \"run\" followed by a newline.\n");
		}
	} else {
		printf("prng-service.txt or it's contents are missing.\n");
		return -1;
	}
}

void write_number() {
	srand(time(NULL));
	char path[27] = "./prng-service.txt";
	char to_write[6];

	int key = rand() % 99999;
	snprintf(to_write, sizeof(to_write), "%d", key);

	FILE* writefile = fopen(path, "w");
	if (writefile != NULL) {
		fputs(to_write, writefile);
		fputs("\n", writefile);
		fclose(writefile);
	}
}

int main() {
	if (read_instructions() > -1) {
		write_number();
	}

	return 0;
}
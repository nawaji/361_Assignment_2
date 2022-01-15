/**************************************
 * Pseudo-random number gen (PRNG Service)
 * tojo@oregonstate.edu
 * 1/12/22
 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// reads from "prng-service.txt"
// returns -1 if txt does not contain "run"
// returns 1 if txt contains "run"
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

		// contains "run"
		if (strncmp("run", buffer, strlen(buffer)) == 0) {
			fclose(readfile);
			return 1;

		// contains something other than "run"
		} else {
			printf("Please provide \"prng-service.txt\" containing");
			printf(" only the word \"run\".\n");
			fclose(readfile);
			return -1;
		}
	
	// blank file or prng-service.txt does not exist
	} else {
		printf("prng-service.txt or it's contents are missing.\n");
		return -1;
	}
}

// function used to write content to a specific file
// overwrites the file if it contained anything previously
void write_file(char* content, char* filename) {
	FILE* writefile = fopen(filename, "w");
	if (writefile != NULL) {
		fputs(content, writefile);
		fclose(writefile);
	}
}

int main() {
	srand(time(NULL));

	if (read_instructions() > -1) {

		// generate our psuedo-random number then write to file
		char to_write[7];
		int key = rand() % 99999;
		snprintf(to_write, sizeof(to_write), "%d", key);
		write_file(to_write, "./prng-service.txt");
	}

	return 0;
}
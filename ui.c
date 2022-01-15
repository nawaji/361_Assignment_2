/**************************************
 * User interface program
 * tojo@oregonstate.edu
 * 1/14/22
 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// reads from specified file and then returns the content
char* read_file(char* filename) {
	char* buffer = malloc(50 * sizeof(char));
	memset(buffer, '\0', sizeof(buffer));

	FILE* readfile = fopen(filename, "r");
	if (readfile != NULL && !feof(readfile)) {
		fgets(buffer, 50, readfile);
	} else {
		return NULL;
	}

	fclose(readfile);
	return buffer;
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

// We will use this function to call the microservices from this
// UI program
void call_program(char* exe) {
	pid_t spawnPID = fork();
	int childStatus;

	switch(spawnPID) {
		case -1:
			perror("fork() failed!\n");
			exit(1);
			break;
		case 0:
			execvp(exe, NULL);
			perror("execvp() errored!\n");
			exit(2);
			break;
		default:
			spawnPID = waitpid(spawnPID, &childStatus, 0);
			break;
	}
}

int main() {
	while (1) {
		printf("\n1: Call the PRNG service.\n2: Call the Image Service.\n3: Display image path.\n4: Quit.\n\n");
		printf("Type a number: ");
		char input[20];
		fgets(input, sizeof(input), stdin);
		printf("\n");

		// Run these in order!
		// 1 - writes "run" to "prng-service.txt" then calls PRNG service
		// 2 - copies "prng-service.txt" to "image-service.txt" then calls IMAGE service
		// 3 - Print path of image
		// 4 - Quit
		switch(atoi(input)) {
			case 1:
				printf("Writing \"run\" to prng-service.txt...\n");
				write_file("run\n", "./prng-service.txt");
				sleep(2);

				printf("Calling PRNG service...\n");
				call_program("prng");
				sleep(1);
				break;
			case 2:
				printf("Copying pseudo-random number from prng-service.txt to image-service.txt...\n");
				char* num = read_file("./prng-service.txt");
				write_file(num, "./image-service.txt");
				sleep(2);

				printf("Calling image service...\n");
				call_program("image");
				sleep(1);
				free(num);
				break;
			case 3: ;
				char* path_name;
				path_name = read_file("./image-service.txt");
				printf("Image path: %s\n", path_name);
				free(path_name);
				break;
			case 4:
				printf("Quitting UI program...\n\n");
				return 0;
				break;
			default:
				printf("Please type a number from the list.\n");
				break;
		}
	}
	return 0;
}
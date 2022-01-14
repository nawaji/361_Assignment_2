#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
	srand(time(NULL));

	if (argc < 2) {
		fprintf(stderr, "USAGE: %s keylength\n", argv[0]);
		fprintf(stderr, "For example: %s 256\n", argv[0]);
		exit(0);
	}
	int keylength = atoi(argv[1]);

	// prints out a letter from A->Z for specified keylength
	for (int i = 0; i < keylength; i++) {
		int key = rand() % 26;

		printf("%c", key + 65);
	}
	printf("\n");

	return 0;
}
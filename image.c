/**************************************
 * ith image picker (Image Service)
 * tojo@oregonstate.edu
 * 1/12/22
 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


// reads from "image-service.txt"
// returns -1 if txt contains non nums
// returns the psuedo-random number in "image-service.txt" if it contains one
int read_instructions() {
	char path[27] = "./image-service.txt";
	char buffer[20];

	FILE* readfile = fopen(path, "r");
	if (readfile != NULL && !feof(readfile)) {
		fgets(buffer, sizeof(buffer), readfile);
		for (int i = 0; i < sizeof(buffer); i++) {
			if (buffer[i] == '\n') {
				buffer[i] = '\0';
				break;
			}

			// cancel if non numbers are found
			if (!isdigit(buffer[i]) && buffer[i] != '\0') {
				printf("image-service.txt contains non-nums.\n");
				fclose(readfile);
				return -1;
			}
		}

		int result = atoi(buffer);
		fclose(readfile);
		return result;

	// blank file or image-service.txt does not exist
	} else {
		printf("image-service.txt or it's contents are missing.\n");
		return -1;
	}
}

// function used to check if file in directory
// is an image (specifically png).
int check_img(char* filename) {
	char* buffer = "png";
	char* ext = strrchr(filename, '.');
	if (!ext || ext == filename) { 
		ext = " ";
	}
	ext = ext + 1;
	return strncmp(buffer, ext, strlen(buffer));
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

// Checks a directory called "/image_service/" within the same
// directory as image.c (this file).
// It will tally up all the files with the specific extension 
// specified in check_img().
// It picks a random file based on the psuedo-random num and writes
// it to "image-service.txt".
int total_images(int num) {
	char *img_path = malloc(50 * sizeof(char));
	char buffer[20] = "./image_service/";
	memset(img_path, '\0', sizeof(img_path));
	strcat(img_path, buffer);

	DIR* currDir = opendir("./image_service/");
	struct dirent *aDir;
	int total = 0;

	// tally images
	while((aDir = readdir(currDir)) != NULL) {
		if (check_img(aDir->d_name) == 0) {
			total++;
		}
	}
	closedir(currDir);

	total = num % total;
	int curr = 0;

	// obtain filename of specified image
	currDir = opendir("./image_service/");
	while(curr < total) {
		aDir = readdir(currDir);
		curr++;
	}

	strcat(img_path, aDir->d_name);
	closedir(currDir);

	// finally write path to image to text file
	write_file(img_path, "./image-service.txt");
	free(img_path);
}

int main() {
	int num = read_instructions();
	if (num > -1) {
		total_images(num);
	}

	return 0;
}
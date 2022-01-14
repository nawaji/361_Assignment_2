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

			if (!isdigit(buffer[i])) {
				printf("image-service.txt contains non-nums.\n");
				return -1;
			}
		}

		int result = atoi(buffer);
		return result;

	} else {
		printf("image-service.txt or it's contents are missing.\n");
		return -1;
	}
}

int check_img(char* filename) {
	char* buffer = "png";
	char* ext = strrchr(filename, '.');
	if (!ext || ext == filename) { 
		ext = " ";
	}
	ext = ext + 1;
	return strncmp(buffer, ext, strlen(buffer));
}

void write_path(char* pathname) {
	char output[27] = "./image-service.txt";

	FILE* writefile = fopen(output, "w");
	if (writefile != NULL) {
		fputs(pathname, writefile);
		fputs("\n", writefile);
		fclose(writefile);
	}
}

int total_images(int num) {
	char *img_path = malloc(50 * sizeof(char));
	char buffer[20] = "./image_service/";
	memset(img_path, '\0', sizeof(img_path));
	strcat(img_path, buffer);

	DIR* currDir = opendir("./image_service/");
	struct dirent *aDir;
	int total = 0;

	while((aDir = readdir(currDir)) != NULL) {
		if (check_img(aDir->d_name) == 0) {
			total++;
		}
	}
	closedir(currDir);

	printf("total images: %d\n", total);
	total = num % total;
	int curr = 0;

	currDir = opendir("./image_service/");
	while(curr < total) {
		aDir = readdir(currDir);
		curr++;
	}

	strcat(img_path, aDir->d_name);
	closedir(currDir);

	write_path(img_path);
	free(img_path);
}

int main() {
	int num = read_instructions();
	if (num > -1) {
		total_images(num);
	}

	return 0;
}
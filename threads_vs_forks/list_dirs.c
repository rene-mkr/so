#include <stdio.h>
#include <dirent.h>

int main() {
    struct dirent *directoryContent;
    char *directoryName = "/Users/ramonorraca/Desktop/Ibero/Clases/2022_Otoño/SistemasOperativos";
    char file_type = '\0';
    DIR  *directory = opendir(directoryName);
    while ((directoryContent = readdir(directory)) != NULL) {
	if (directoryContent->d_type == 4) {
	    file_type = 'd';
	} else if (directoryContent->d_type == 8) {
	    file_type = '-';
	} else {
	    file_type = '?';
	}
        printf("%u (%c) - %s\n", directoryContent->d_reclen, file_type, directoryContent->d_name);
    }
    // printf("\n\nDirectory: %p\n\n", (directoryContent));
    closedir(directory);
}

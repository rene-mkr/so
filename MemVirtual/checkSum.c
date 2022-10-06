#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>

/* Variable global para mejor legibilidad */
int fd; // Archivo a leer


char *mapFile(char *filePath) {
    /* Abre archivo */
    fd = open(filePath, O_RDONLY);
    if (fd == -1) {
    	perror("Error abriendo el archivo");
	    return(NULL);
    }

    /* Mapea archivo */
    struct stat st;
    fstat(fd,&st);
    int fs = st.st_size;

    char *map = mmap(0, fs, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
    	close(fd);
	    perror("Error mapeando el archivo");
	    return(NULL);
    }

  return map;
}

int hazChecksum(char *filename) {

    /* Lee archivo */
    char *map = mapFile(filename);
    if (map == NULL) {
      exit(EXIT_FAILURE);
      }

    /* Obten tamaño */
    struct stat st;
    fstat(fd,&st);
    long fs = st.st_size;

    /* Guarda en Long */
    long sum = 0;

    for(long i= 0; i<fs; i++) {
    	// Suma
    	sum += map[i];
    }

    /* resultado */
    printf("La suma es 0%lx \n", sum);

    if (munmap(map, fd) == -1) {
      perror("Error al desmapear");
    }

    close(fd);
    
   return 0;

}

int main(int argc, char const *argv[])
{
    /* El archivo se da como parametro */
    if (argc != 2) {
        printf("Se usa %s <archivo> \n", argv[0]);
        return(-1);
    }

    hazChecksum((char *)argv[1]);

    return 0;
}

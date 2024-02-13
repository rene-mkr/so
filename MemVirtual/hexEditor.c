#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <sys/stat.h>
#include <sys/mman.h>

/* Variable global para mejor legibilidad */
int fd; // Archivo a leer


char *hazLinea(char *base, int dir) {
	char linea[100]; // La linea es mas pequeña
	int o=0;
	// Muestra 16 caracteres por cada linea
	o += sprintf(linea,"%08x ",dir); // offset en hexadecimal
	for(int i=0; i < 4; i++) {
		unsigned char a,b,c,d;
		a = base[dir+4*i+0];
		b = base[dir+4*i+1];
		c = base[dir+4*i+2];
		d = base[dir+4*i+3];
		o += sprintf(&linea[o],"%02x %02x %02x %02x ", a, b, c, d);
	}
	for(int i=0; i < 16; i++) {
		if (isprint(base[dir+i])) {
			o += sprintf(&linea[o],"%c",base[dir+i]);
		}
		else {
			o += sprintf(&linea[o],".");
		}
	}
	sprintf(&linea[o],"\n");

	return(strdup(linea));
}

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
    long fs = st.st_size;

    char *map = mmap(0, fs, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
    	close(fd);
	    perror("Error mapeando el archivo");
	    return(NULL);
    }

  return map;
}

int leeChar() {
  int chars[5];
  int ch,i=0;
  nodelay(stdscr, TRUE);
  while((ch = getch()) == ERR); /* Espera activa */
  ungetch(ch);
  while((ch = getch()) != ERR) {
    chars[i++]=ch;
  }
  /* convierte a numero con todo lo leido */
  int res=0;
  for(int j=0;j<i;j++) {
    res <<=8;
    res |= chars[j];
  }
  return res;
}


int edita(char *filename) {
	
    /* Limpia pantalla */
    clear();

    /* Lee archivo */
    char *map = mapFile(filename);
    if (map == NULL) {
      exit(EXIT_FAILURE);
      }
    
    for(int i= 0; i<25; i++) {
    	// Haz linea, base y offset
    	char *l = hazLinea(map,i*16);
	    move(i,0);
	    addstr(l);
    }
    refresh();

    int c = getch();
	
    while (c != 26) {
	    switch (c) {
		    case KEY_LEFT:
			    break;
	    }
	    c = getch();
    }

    if (munmap(map, fd) == -1) {
      perror("Error al desmapear");
    }
    close(fd);
    
   return 0;

}

int main(int argc, char const *argv[])
{
	initscr();
	raw(); 
	keypad(stdscr, TRUE);	/* Para obtener F1,F2,.. */
	noecho();

    /* El archivo se da como parametro */
    if (argc != 2) {
        printf("Se usa %s <archivo> \n", argv[0]);
        return(-1);
    }

    edita((char *)argv[1]);

    endwin();
    
    return 0;
}

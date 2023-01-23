#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


void* crea_memoria_compartida(size_t tam) {
  // Crea un buffer que se pueda leer y escribir:
  int proteccion = PROT_READ | PROT_WRITE;

  // Se crea compartido, claramente, 
  // pero el que sea anonimo significa 
  // que solo este proceso puede verlo:
  int visibilidad = MAP_SHARED | MAP_ANONYMOUS;

  // Los parametros adicionales de `mmap()` no son importantes en este caso,
  // 'man mmap' explica su proposito.
  return mmap(NULL, tam, proteccion, visibilidad, -1, 0);
}

int main() {
  char men_papa[] = "hola a todos";  // El papa escribe este mensaje
  char men_hijo[] = "adios a todos"; // El hijo escribe este

  int num_papa = 56;
  int num_hijo = 7;
  
  void* shmem = crea_memoria_compartida(sizeof(int)*5); // 128 bytes solamente

  //memcpy((int *)shmem, &num_papa, sizeof(num_papa));

  int *numero = (int *)shmem;

  for (int i=0; i<5; i++)
    numero[i] = rand() % 50000;
  
  int pid = fork();

  if (pid == 0) {
    for (int i=0; i<5; i++)
      printf("El hijo lee: %d\n", numero[i]);
    //memcpy(shmem, &num_hijo, sizeof(num_hijo));
    numero[0] = num_hijo;
    printf("El hijo escribe: %d\n", *numero);

  } else {
    printf("El papa lee: %d\n", *(int *) shmem);
    sleep(1);
    printf("Despues de 1s, el papa lee: %d\n", *(int *) shmem);
    for (int i=0; i<5; i++)
      printf("El papa lee: %d\n", numero[i]);
    int status=0;
    wait(&status);
  }
}

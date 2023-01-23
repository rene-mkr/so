#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Estructura mensajes
typedef struct {
  long mtype;
  char mtxt[100];
} mens;

int main() {
  char men_papa[] = "hola a todos";  // El papa escribe este mensaje
  char men_hijo[] = "adios a todos"; // El hijo escribe este

  int num_papa = 56;
  int num_hijo = 7;

  int numero;

  // Paso de mensajes - inicializacion
  
  key_t key = ftok("prueba",123);
  int qid = msgget(key,0666 | IPC_CREAT);

  mens men;
  
  int pid = fork();

  if (pid == 0) {
    numero = num_hijo;
    printf("El hijo escribe: %d\n", numero);

    men.mtype=1;
    strcpy(men.mtxt,men_hijo);
    sleep(5);
    // Avisa acabaste
    msgsnd(qid,&men,sizeof(men), MSG_NOERROR);
    
  } else {
    strcpy(men.mtxt,men_papa);
    numero = num_papa;
    printf("El papa lee: %d\n", numero);
    printf("El papa tiene el mensaje: %s\n", men.mtxt);
    
    // Espera al hijo
    msgrcv(qid,&men,sizeof(men),1,MSG_NOERROR);
    printf("Recibi %s\n",men.mtxt);

    printf("El papa lee: %d\n", numero);
    int status=0;

    wait(&status);
  }
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
  // Variables
  int a = 20;
  
  // make two process which run same
  // program after this instruction
  int pid = fork();
  if (pid > 0) {
    // Soy el papa
    int status; // Con el que acabo el hijo
    wait(&status);
    printf("El estatus fue %d\n",status);
  }
  else
  {
    a = 50;
    printf("Soy el hijo\n I am %d, a = %d\n",pid,a);
    sleep(10);
    execl("/usr/bin/ls", "/usr/bin/ls", "-l", (char *)NULL);
  }
  printf("Soy el papa\n I am %d, a = %d \n",pid,a);
  return 0;
}

#include <stdio.h>
#include <readline/readline.h>

int main() {

  char *name = readline("Dime tu nombre:");

  printf("¡Hola %s!\n",name);

  return 0;
}

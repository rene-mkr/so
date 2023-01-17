/*
  ============================================================================
  Name        : prueba_simple.c
  Author      : Rene
  Version     : 0.1
  Copyright   : Your copyright notice
  Description : ejemplo con pthreads
  ============================================================================
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int dato=0; /* dato compartido por los hilos */
int otrodato=0;
void* resta(); /* hilo 1 */
void* suma(); /* hilo 2 */
bool flag[2]; /* 0 falso y 1 verdad */
int turn; // Quien es el turno primero

  typedef struct params {
    int v;
    char *m;
  } params;



int main(int argc, char *argv[]) {
  pthread_t tid1,tid2; /* the thread identifier */
  pthread_attr_t attr; /* set of attributes for the thread */
  if (argc != 4) {
    fprintf(stderr, "usage: %s <ini> <sum> <sub>\n",argv[0]);
    /*exit(1);*/
    return -1;
  }
  if (atoi(argv[1]) < 0) {
    fprintf(stderr, "Argument %d must be non-negative\n", atoi(argv[1]));
    /*exit(1);*/
    return -1;
  }
  srand(0);

  /* El parametro que recibo es el valor inicial de dato */
  dato = atoi(argv[1]);
  int sum = atoi(argv[2]);
  int res = atoi(argv[3]);

	
  /* get the default attributes */
  pthread_attr_init(&attr);

  params p = {.v=res,.m="Hola"};

  /* create the thread 1*/
  pthread_create(&tid1, &attr, resta, (void *)&p);
  
  params p1 = {.v=sum,.m="Adios"};
  
  /* create the thread 2*/
  pthread_create(&tid2, &attr, suma, (void *)&p1);
	
  usleep(500000);
  /* espera a los hilos */
  // pthread_join(tid1, NULL);
  // pthread_join(tid2, NULL);
  
  printf("dato = %d\n", dato);
  printf("otrodato = %d\n", otrodato);
}
/**
 * Este hilo resta
 */
void* resta(void * ps) {
  /* Inicio resta */

  params *p = (params *) ps;

  printf("%s\n",p->m);
  int t=dato;
  for (int i = 0; i < p->v*10; i++) { // Haz cosas
    usleep(rand() % 500);
    if (i % 10 == 0) {
      t--;
    }
  }

  dato = t;
  pthread_exit(0);
}
/**
 * Este hilo suma
 */
void* suma(void * ps) { 

  params *p = (params *) ps;

  printf("%s\n",p->m);
  int t=dato;

  for (int i = 0; i < p->v*10; i++) { // Haz cosas
    usleep(rand() % 500);
    if (i % 10 == 0) {
      t++;
    }
  }
  // sleep(1);

  dato = t;


  pthread_exit(0);
}

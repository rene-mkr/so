// Define header file if not defined.
#ifndef shmem_messenger_h
#define shmem_messenger_h

// Import libraries to be used.
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// 
#define STORAGE_ID "/OBJ_MEM_COM"
#define STORAGE_SIZE 128
#define DATA "Soy PID %d, Hola Curso de Sistemas Operativos"

#endif
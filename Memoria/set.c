#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define STORAGE_ID "/OBJ_MEM_COM"
#define STORAGE_SIZE 128
#define DATA "Soy PID %d, Hola Curso de Sistemas Operativos"

int main(int argc, char *argv[])
{
	int res;
	int fd;
	int len;
	pid_t pid;
	void *addr;
	char data[STORAGE_SIZE];

	pid = getpid();
	sprintf(data, DATA, pid);

	// obten objeto de memoria compartida (NO un archivo)
	fd = shm_open(STORAGE_ID, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open");
		return 10;
	}

	// aumenta el objeto de memoria compartida ya
	// que es de 0 por omision
	res = ftruncate(fd, STORAGE_SIZE);
	if (res == -1)
	{
		perror("ftruncate");
		return 20;
	}

	// mapea en la memoria del proceso
	addr = mmap(NULL, STORAGE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("mmap");
		return 30;
	}

	// pon datos en memoria
	len = strlen(data) + 1;
	memcpy(addr, data, len);

	// espera a que lo lean
	sleep(30);

	// termina mmap
	res = munmap(addr, STORAGE_SIZE);
	if (res == -1)
	{
		perror("munmap");
		return 40;
	}

	// termina shm_open 
	fd = shm_unlink(STORAGE_ID);
	if (fd == -1)
	{
		perror("unlink");
		return 100;
	}

	return 0;
}

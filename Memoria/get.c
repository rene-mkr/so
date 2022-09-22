
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define STORAGE_ID "/OBJ_MEM_COM"
#define STORAGE_SIZE 32

int main(int argc, char *argv[])
{
	int res;
	int fd;
	char data[STORAGE_SIZE];
	pid_t pid;
	void *addr;

	pid = getpid();

	// obten descriptor de memoria compartida (NOT un archivo)
	fd = shm_open(STORAGE_ID, O_RDONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open");
		return 10;
	}

	// mapea a la memoria del proceso
	addr = mmap(NULL, STORAGE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("mmap");
		return 30;
	}

	// pon datos en la memoria
	memcpy(data, addr, STORAGE_SIZE);

	printf("Lei de memoria compartida: \"%s\"\n", data);


	printf("PID %d: ",pid);

	return 0;
}

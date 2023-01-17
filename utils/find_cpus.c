/*
 ============================================================================
 Name        : find_cpus.c
 Author      : https://stackoverflow.com/questions/4586405/how-to-get-the-number-of-cpus-in-linux-using-c
 Version     :
 Copyright   : No se conoce
 Description : Encontrar el numero de CPUs en el procesador
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

int num_cpus() {

	unsigned  int	eax=11,ebx=0,ecx=1,edx=0;
	asm
	volatile
	( " cpuid "
	:  "=a"  ( eax ) ,
	"=b"  ( ebx ) ,
	"=c"  ( ecx ) ,
	"=d"  ( edx )
	:  "0"  ( eax ) ,  "2"  ( ecx )
	:  ) ;
	printf("Cores :  % d\nThreads :  % d\nActual  thread :  % d\n", eax , ebx , edx);
	
	return eax*ebx;
	
}

int get_ncpus() {
	// Return processors available
	return get_nprocs();
}

int main(void) {
	
	int num=num_cpus();
	
	printf("Encontre %d cpus \n",num);

	num=get_ncpus();
	
	printf("Encontre %d cpus \n",num);

	return EXIT_SUCCESS;
}

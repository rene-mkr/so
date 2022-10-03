#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/utsname.h>

/**
 * The following code comes from the Geeks for Geeks website, it displays information about the system.
 * 
 * Source: https://www.geeksforgeeks.org/getting-system-and-process-information-using-c-programming-and-shell-in-linux/
 *
 * The code emulates how the uname -a command works.
 *
 */
int main() {
   struct utsname buf1;
   errno =0;
   if (uname(&buf1)!=0) {
      perror("uname doesn't return 0, so there is an error");
      exit(EXIT_FAILURE);
   }
   printf("System Name = %s\n", buf1.sysname);
   printf("Node Name = %s\n", buf1.nodename);
   printf("Version = %s\n", buf1.version);
   printf("Release = %s\n", buf1.release);
   printf("Machine = %s\n", buf1.machine);
}

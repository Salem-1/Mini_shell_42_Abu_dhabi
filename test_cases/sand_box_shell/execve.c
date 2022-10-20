#include <stdio.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	//this program takes the path to the executable then the executable name then parameters
	char *path = argv[1];
 	char *argVec[] = {argv[2], argv[3], NULL};
	char *env[] = { NULL};

	printf("===============================\n");
	execve(path, argVec, env);
	printf("The program failed execution\n");
	return (0);
}
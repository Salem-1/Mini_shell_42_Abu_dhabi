#include <unistd.h>
#include<sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/*creating program that prints from 1 to 10 using fork()*/
int main()
{
	int	pid;
	int	n;
	int	i = 0;

	pid = fork();
	if (pid == 0)
	{
		printf("Child process id = %d\n", getpid());
		n = 1;
	}
	else
	{
		n = 6;
		//waiting for the child process to finish 
		//execution first
		int w = wait(NULL);
		printf("Wait return value = %d\n", w);
	}
	while (i < 5)
	{
		printf("%d ", n + i);
		i++;
	}
	//printing new line after the end of the parent process
	// if (pid != 0)
	// 	printf("\n");

}
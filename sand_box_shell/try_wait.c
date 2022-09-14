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
		n = 1;
		execve(env, "cat", "file.txt");
	}
	else
	{
		n = 51;
		//waiting for the child process to finish 
		//execution first
		wait(NULL);
	}
	while (i < 50)
	{
		printf("%d ", n + i);
		i++;
	}
	//printing new line after the end of the parent process
	// if (pid != 0)
	// 	printf("\n");

}
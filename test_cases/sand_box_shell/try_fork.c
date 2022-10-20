#include <unistd.h>
#include <stdio.h>

int main()
{
	int	pid;
	printf("Inside main the original PID = %d\n", getpid());
	//fork() will separate the program execution into 2 proccesses 
	//child assigning 0 to it and parent with the same process id.
	pid = fork();
	if (pid == 0)
	{
		printf("Inside child process, getpid(pid) = %d, pid = %d, parent = %d\n",
		getpid(), pid, getppid());
	}
	else
		printf("Inside parent process,  getpid(pid) = %d, pid = %d parent = %d\n",
		getpid(), pid, getppid());
}
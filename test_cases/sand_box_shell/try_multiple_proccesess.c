#include <unistd.h>
#include <stdio.h>

int main()
{
	int	pid1;
	int	pid2;
	printf("Inside main the original PID = %d\n\n\n", getpid());
	//fork() will separate the program execution into 2 proccesses 
	//child assigning 0 to it and parent with the same process id.
	pid1 = fork();
	pid2 = fork();
	if (pid1 == 0 && pid2 == 0)
	{
		printf("Inside grand child process, getpid(pid) = %d, pid1 = %d, pid2 = %d\n",
		getpid(), pid1, pid2);
	}
	else if (pid1 == 0 && pid2 != 0)
	{
		printf("Inside Child process who is now parent,  getpid(pid) = %d, pid1 = %d, pid2 = %d\n",
		getpid(), pid1, pid2);
	}
	else if (pid1 != 0 && pid2 == 0)
	{
		printf("Inside legitimate child process,  getpid(pid) = %d, pid1 = %d, pid2 = %d\n",
		getpid(), pid1, pid2);
	}
	else if (pid1 != 0 && pid2 != 0)
	{
		printf("Inside Ana Baba Yala process,  getpid(pid) = %d, pid1 = %d, pid2 = %d\n",
		getpid(), pid1, pid2);
	}

}
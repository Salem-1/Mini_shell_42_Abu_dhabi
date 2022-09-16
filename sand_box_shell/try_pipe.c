#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main()
{
	int	pid;
	int fd[2];
	int x;
	int y;

	printf("Inside main the original PID = %d\n", getpid());

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		x = 3;
		write (fd[1], &x, 4);
		printf("Inside child process, getpid(pid) = %d, pid = %d, parent = %d\n",
		getpid(), pid, getppid());
		printf("in child y = %d\n", y);
		close(fd[1]);
	}
	else
	{
		wait (NULL);
		close(fd[1]);
		read(fd[0], &y, 4);
		close(fd[1]);
		printf("Inside parent process,  getpid(pid) = %d, pid = %d parent = %d\n",
		getpid(), pid, getppid());
	}
	if (pid != 0)
		printf("y i s %d\n", y);
}
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
int x = 1;

int main ()
{
	int	pid;
	int	fd;
	char *path = "/usr/bin/top";
	char *args[] = {"top", NULL};
	char *env[] = {NULL};
	
	printf("before forking parent %d\n\n\n", getpid());
	fd = open("trialfile.txt", O_RDWR | O_CREAT);
	if (fd == -1)
		perror("open");
	 dup2(fd ,1);
	//dup2(1, 1);
	pid = fork();
	if (pid == 0)
	{

		if (execve(path , args, NULL) == -1)
			perror("execve");
		return (0); 
	}
	else 
	{
		sleep(1);
		kill(pid, SIGKILL);
		wait(NULL);
	}
}

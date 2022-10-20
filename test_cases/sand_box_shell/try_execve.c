#include <unistd.h>
#include <stdio.h>

int main()
{
	//path of the executable
	char *cmd = "/bin/ls";
	//list of arguments, start with the name or path of the executable
	char *args[] = {"ls", "-la", NULL};
	//list of the environment variable, you can assign here, NULL terminated list
	char *env[] = {NULL};
	//executing the command
	execve(cmd, args, env);
	//if successful, it should close the program, otherwise it failed execution
	printf("if you see this, it means the execution failed\n");
	return (0);
}

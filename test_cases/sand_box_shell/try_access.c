#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int access(const char *path, int amode);
int main()
{
	char	*a ;
	int		found_executable;

	while (1)
	{
		//prompt the user for input with the message below
		a = readline("minishel tester $> ");
		//check if the file exists and has execution permission
		found_executable = access(a, X_OK);

		if (found_executable == 0)
			printf("Found %s and I can execute\n", a);
		else
		{
			//if not found check the existance of the file 
			//you can check ERRNOM for [ENOENT] intead of this condition
			found_executable = access(a, F_OK);
			if (!found_executable)
				printf("the %s exist but you are not allowed to execute it\n", a);
			else
				printf("File %s doesn't exist\n", a);
		}
		//saved it to a
		//then print it back to the user 
		// printf("%s\n", a);
		add_history(a);
		free(a);
	}
}
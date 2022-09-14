#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main()
{
	char *a ;

	while (1)
	{
	//prompt the user for input with the message below
	a = readline("minishel tester $> ");
	//saved it to a
	//then print it back to the user 
	printf("%s\n", a);
	free(a);
	}
}
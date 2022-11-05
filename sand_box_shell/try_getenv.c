#include <stdlib.h>
#include <stdio.h>

int main ()
{
	char *get_me_value_from_env;

	//get any value from the environment variables if you give the vriable name
	get_me_value_from_env = getenv("LOGNAME");
	printf("Logname = %s\n", get_me_value_from_env);
	//no need to free the returned char *, I tested this myself using valgrind
}
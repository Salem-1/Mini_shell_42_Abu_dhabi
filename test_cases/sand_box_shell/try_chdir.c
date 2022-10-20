#include <stdio.h>
#include <unistd.h>

int main ()
{
	char	buf[4096];
	char *new;
	size_t	size = 200;

	//malloc with the maximum path size in linux according to the BSD Library functoin manual 
	//"Obviously, buf should be at least MAXPATHLEN bytes in length."

	//return pointer of copy of the current absoloute path 
	new = getcwd(buf, size);
	printf("%s\n", new);

	//cd to ..
	int result = chdir("..");
	printf("call result = %d\n", result);
	//Demonstrating the new path after changing the directory
	new = getcwd(buf, size);
	printf("%s\n", new);
	//must free the allocated buffer
	return (0);
}

#include <unistd.h>
#include <stdio.h>

int	main()
{
	//deletes the file 
	int result = unlink("trialfile.txt");
	if (result)
	{
		printf("result call = %d\n", result);
		//print the corresponding error message from the erronom
		perror("unlink");
	}else
		printf("successful deletion of trialfile.txt result of the call = %d \n", result);
	return (0);
}

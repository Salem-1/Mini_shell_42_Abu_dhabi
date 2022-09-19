#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/*
	this program is overcomlicated and not needed for the project, 
	The implementation of pipes is wrong as I shouldn't use same pipe 
	to read and write to in the same process, 
	The wait is wrongly place to fix the wrong pipe usage,
	Whoever it's nice lesson gave me a glimpse how to debug nested proccesses
*/

int main ()
{
	int fd1[2]; 
	int fd2[2];
	int sum1, sum2, child1, child2, sum3, tmp_total;
	int pid1, pid2, start, end;
	int arr[] = {1, 2, 3 , 4, 5, 6, 7, 8, 9, 10};

	tmp_total = 0;
	pipe(fd1);
	pipe(fd2);
	pid1 = fork();
	pid2 = fork();
	printf("count me\n");
	if (pid1 == 0 && pid2 == 0)
	{
		start = 0;
		end = 2;
		//grand child
	}
	else if (pid1 == 0 && pid2 != 0)
	{
		start = 2;
		end = 4;
		//child who is parent now
	}
	else if (pid1 != 0 && pid2 == 0)
	{
		start = 4;
		end = 7;
		//legitimate child
	}
	else if (pid1 != 0 && pid2 != 0)
	{
		//Grand parent
		// usleep(400);
		start = 7;
		end = 10;
		waitpid(pid1, NULL, 0);
	}

	for (int i = start; i < end; i++)
	{
		tmp_total += arr[i];
	}


	if (pid1 == 0 && pid2 == 0)
	{
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		
		write (fd2[1], &tmp_total, 4);
		close(fd2[1]);
		printf("tmp_total in grand child = %d\n", tmp_total);
		//grand child

	}
	else if (pid1 == 0 && pid2 != 0)
	{
		//this approach is tottaly wrong, 
		//you shouldn't read and write at the same pipe, 
		//use one pipe to read from and other pipe to write to
		printf("tmp_total in child who is parent now= %d\n", tmp_total);
		close(fd1[0]);
		close(fd1[1]);
		read(fd2[0], &sum1, 4);
		sum2 = tmp_total;
		sum2 += sum1;
		close(fd2[0]);
		//child who is parent now
		printf("###############sum2 is %d\n", sum2);
		write(fd2[1], &sum2, 4);
		// usleep(10);
		close(fd2[1]);
		// waitpid(pid2, NULL, 0);

	}
	else if (pid1 != 0 && pid2 == 0)
	{
		//legitimate child
		close(fd2[0]);
		close(fd2[1]);
		close(fd1[0]);
		write(fd1[1], &tmp_total, 4);
		printf("tmp_total in lgitimate child= %d\n", tmp_total);
		close(fd1[1]);
	}
	else
	{
		//Grand parent
		printf("tmp_total in grand parent= %d\n", tmp_total);
		close(fd1[1]);
		close(fd2[1]);
		read(fd1[0], &sum1, 4);
		read(fd2[0], &sum2, 4);
		close(fd1[0]);
		close(fd2[0]);
		tmp_total += sum1;
		tmp_total += sum2;
		printf("total sum = %d,                   sum1 = %d, sum2 = %d\n", tmp_total, sum1, sum2);
		// usleep(100);
		// waitpid(pid1, NULL, 0);
		
		// wait(NULL);
		// wait(NULL);
	}
	return (0);
}
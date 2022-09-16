#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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
		start = 7;
		end = 10;
	}

	for (int i = start; i < end; i++)
	{
		tmp_total += arr[i];
	}

	//pipes operations
	if (pid1 == 0 && pid2 == 0)
	{
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		sum1  = tmp_total;
		write (fd2[1], &sum1, 4);
		close(fd2[1]);
		printf("tmp_total in grand child = %d\n", tmp_total);
		//grand child
	}
	else if (pid1 == 0 && pid2 != 0)
	{
		close(fd1[0]);
		close(fd1[1]);
		read(fd2[0], &sum1, 4);
		sum2 = tmp_total;
		sum2 += sum1;
		close(fd2[0]);
		write(fd2[1], &sum2, 4);
		close(fd2[1]);
		//child who is parent now
		printf("tmp_total in child who is parent now= %d\n", tmp_total);
		wait(NULL);
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
		close(fd1[1]);
		close(fd2[1]);
		read(fd1[0], &sum1, 4);
		read(fd2[0], &sum2, 4);
		close(fd1[0]);
		close(fd2[0]);
		tmp_total += sum1;
		tmp_total += sum2;
		printf("total sum = %d\n", tmp_total);
		printf("tmp_total in grand parent= %d\n", tmp_total);
		wait(NULL);
	}
}
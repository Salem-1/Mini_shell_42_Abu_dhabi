#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
int main()
{
	 struct stat *restrict buf;
	
	buf = malloc(sizeof(struct stat));
	int fd = open("try_cwd.c", O_RDONLY);
    if (fd == -1)
		perror("open");
	//getting the file information
	fstat(fd, buf);
	//printing the file size in bytes
	printf("file size = %ld\n", buf->st_size);
	free(buf);
}
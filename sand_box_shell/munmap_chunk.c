
//reproducing munmap_chunk() : invalid point error
//source :https://stackoverflow.com/questions/32118545/munmap-chunk-invalid-pointer
#include <stdio.h>
#include <stdlib.h>

char *first()
{
	char *word = malloc(sizeof(char) * 10);
	word[0] = 'a';
	word[1] = 'b';
	word[2] = '\0';
	return word;
}

char *second()
{
	char *word = malloc(sizeof(char) * 10);
	word = "ab";
	return word;
}

int main()
{
	char *out = first();
	printf("%s", out);
	free(out);
	out = second();
	printf("%s", out);
	free(out);
	return 0;
}

/**
 this error happeneed because in line 19 the pointer
 was changed to point away from the allocated char *, 
 then when freeing it on line 30 it tries to free memory that was
 not allocated by malloc or ft_calloc
*/
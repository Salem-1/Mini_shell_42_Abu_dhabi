#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
	char	*buf;
	char *new;
	size_t	size = 200;

	//malloc with the maximum path size in linux according to the BSD Library functoin manual 
	//"Obviously, buf should be at least MAXPATHLEN bytes in length."
	buf = malloc(4098);
	//return pointer of copy of the current absoloute path 
	new = getcwd(buf, size);
	printf("%s\n", new);
	//must free the allocated buffer
	free(buf);
	return (0);
}

//maximum path length
//4098 bytes
//ref: https://www.google.com/search?q=maximum+path+length+%3Binux&sxsrf=ALiCzsZ0r7uA-MgANZrUtcIbfq451zNURQ%3A1663556423974&ei=R9snY7KAO5eRhbIPo9a1kAI&ved=0ahUKEwjyv9vN7p_6AhWXSEEAHSNrDSIQ4dUDCA4&uact=5&oq=maximum+path+length+%3Binux&gs_lcp=Cgdnd3Mtd2l6EAMyBQghEKABMgUIIRCgAToHCCMQsAMQJzoKCAAQRxDWBBCwAzoFCAAQgAQ6BAgAEEM6BggAEB4QFkoECEEYAEoECEYYAFDoA1jvD2D4EGgBcAF4AIAB2AGIAcoHkgEFMC40LjGYAQCgAQHIAQjAAQE&sclient=gws-wiz
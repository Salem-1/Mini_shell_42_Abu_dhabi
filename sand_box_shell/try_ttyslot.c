#include <unistd.h>
#include <stdio.h>
int main ()
{
	int a = ttyslot();
	printf("%d tty is the terminal that controls our process\n", a);
}
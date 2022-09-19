                                            Bism Ellah Elra7man Elra7eem


Mininshell specs:
----------------
1-  Display a prompt when waiting for new command
2-  Having working history?
3-  Search and launch right executable:
    	a) Relative path
    	b) Absoloute path
4-  Maximum one global variable
5-  Not interpret:
    	a)Unclosed quotes "																																
		b)special characters that are not required by the subject as  \  ;
6-  Handle ' which should prevent the shell from interpreting the metacharachters in 
the qouted sequence
7-  Handle " which sould prevent the shell form interpreting the metacharachters 
except for $ (dollar sign)
8-  handle redirection:
	a) < redirect input
	b) > redirect output
	c) << should be:
			given delimeter 
			then read the input
			until the line containing delimeter is seen
	N.B: It doesn't have to update the history.																									' 
	d) >> redirect output in append mode 
9-  Implement pipes: output of each command | connected to the input of the next command via a pipe.
10- Handle environment variables, should expand to thier values ($LE)
11- Handle $ and ?, which should be expand to the exit status of the most recently
executed foreground pipeline.
12- Handle: 
	CTR-C    interactive mode ---> Display new prompt in a new line
	CTR-D    interactive mode ---> exit the shell
	CTR-/    interactive mode ---> do nothing
13- Implementation of:
		a) echo 
		b) echo -n 
		c) cd with only relative or absoloute path
		d) export with no options
		e) unset with no options
		f) env with no options or arguments
		g) exit with no options





Questions:
1-  What is a prompt?
	the tesxt in the terminal that shows that the computer is ready to take commands
	ex:
	ahsalem@lab3r3s12 minishell % 
	minishell$>
	C:\Windows>
2-  How to display a prompt when waiting new command?
3-  What is bash terminal working history?
4-  How to have one?
5-  How to search for commands in relative and absoloute path?
6-  How to execute variables in relative and absoloute path?
7-  What are special characters in Bash terminal?
8-  What is the use of '' singel quote in bash terminal?
9-  What are metacharachters?
10- How do bash handle single quotes with metacharachters?
11- How doe bash handle double qoutes with metacharachters?
12- Behavior of double quotes along with the $ dollar sign?
13- What do > do?
14- What do < do?
15- What do >> do?
16- What do << do?
17- Dig deep in the behavior of pipes | 
18- What are environment variables, and what are their uses?
19- What is the use of $  '?' ?
20- What is  $ expansion to exit status means?
21- What is executed foreground pipeline, what is the pipeline, and what is meant by
foreground?
22- What is the meaning of TOKENS?
23- Dig deep in CTR-C 
24- What do the CTR-D & CTR-/ signals do
25- What is the behavior of echo, echo -n, cd with relative and absoloute path, export with no options, 
usent with no options env with no options or arguments, exit with no options?




allowed functions:
-------------------



/*---------------------------------------------------*/
ttyslot:
-------
Get the tty number of the terminal that controls the proceeses.

Declaration:
-----------
  int
     ttyslot(void);
/*---------------------------------------------------*/
fstat:
----
Get information about regular files, 
/*---------------------------------------------------*/
lstat:
------
Get information about linked file.

Declaration:
------------
int
     fstat(int fildes, struct stat *buf);

Example:
--------
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
/*---------------------------------------------------*/
fstat:
-----
Obtain information about opened filed using it's file descriptor '

Declartion:
----------
 #include <sys/stat.h>
   int
     fstat(int fildes, struct stat *buf);
/*---------------------------------------------------*/
unlink:
-------
Unlink filename which means IT DELETE THAT FILE, however if there are 
other filenames linked to this file (content I mean) it will remain.
//ref : https://www.gnu.org/software/libc/manual/html_node/Deleting-Files.html#:~:text=The%20unlink%20function%20deletes%20the,in%20the%20header%20file%20unistd.
Declaration:
-----------
int unlink (const char *filename);

Example:
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

/*---------------------------------------------------*/
chdir:
-----
Changes the directory to the desired location.

Declaratoin:
int chdir(const char *path);

example: 
--------
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

/*---------------------------------------------------*/
ttyname
Get device name of the terminal using file descriptor of the terminal where istty() ==  TRUE.

Declaration:
------------
     char *
     ttyname(int fd);
/*---------------------------------------------------*/
isatty:
-------
Determine if the filename refered by is terminal of not.

Declaration:
------------
 int
     isatty(int fd); 
/*---------------------------------------------------*/
ioctl:
------
Input output control, used for drivers to communicate with kernel, also it has use with the terminal as follows:
https://en.wikipedia.org/wiki/Ioctl#:~:text=In%20computing%2C%20ioctl%20(an%20abbreviation,completely%20on%20the%20request%20code.One use of ioctl in code exposed to end-user applications is terminal I/O.

Unix operating systems have traditionally made heavy use of command-line interfaces.
The Unix command-line interface is built on pseudo terminals (ptys), which emulate hardware 
text terminals such as VT100s. A pty is controlled and configured as if it were a hardware device, 
using ioctl calls. For instance, the window size of a pty is set using the TIOCSWINSZ call. 
The TIOCSTI (terminal I/O control, simulate terminal input) ioctl function can push a character into a device stream.[4]
---
Can be used to prevent blocking systemcalls, for example when using wirte() it block the system call till it finishes the 
execution, IOCTL() with certain flag can prevent this blockage,
Usage in heredock, you can lear it then inshalla
/*---------------------------------------------------*/
getenv:
-------
return the vlaue of specific enviroment variable;


Declaration:
------------
 #include <stdlib.h>

     char *
     getenv(const char *name);

example:
--------
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
/*---------------------------------------------------*/
getcwd:
-------
Get the current working directory,

Return:
Copy of the path as char * 
Declartion:
------------
#include <unistd.h>

     char *
     getcwd(char *buf, size_t size);


example: 
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
/*---------------------------------------------------*/
sigemptyset:
------------
Has something to do with zeroing the blocked signals which meansit
will allow all signals 
/*---------------------------------------------------*/
sigaddset:
----------
has something to  do with blocking some signals or allowing others
/*---------------------------------------------------*/
signal:
-------
recieve signal, then execute your custom handler function
for example to recieve signal SIGINT, with sigintHandler()
to do something after recieving this signal.
void sigintHandler(int SIGINT);
signal(SIGINT, &sigintHandler);

/*---------------------------------------------------*/
sigaction:
----------
Also used to recieve signals, here is a usage example:

void sigintHandler(int SIGINT);
struct sigaction sa;
sa.sa_action = sigintHandler;
sigaction(SIGINT, &sa, NULL);
/*---------------------------------------------------*/

kill:
-----
sending signals to specific pid
int kill(pid_t pid, int signal);
/*---------------------------------------------------*/

opendir:
--------
return pointer to directory entry,which means it gives useful
information and control over certain directory
readdir:
--------
Get useful information out of the opened direcory like subdirs and files
look at the struct in the comment below for more info
closedir:
--------
close the opened directory after usage


usage:
------
In searching the path enviroment variable for certain executable
as followes:
DIR *dest ;
struct dirent de; //directory entry apprevation
dest= opendir("/searched/path/usr/bin");

while ((de = readdir(dest)) != NULL)
{
	if (found)
		return (found);
	else
		continue ;
}

Example:
-------
#include <dirent.h>
#include <stdio.h>

int main()
{
	DIR *current_dir;
	struct dirent *de;

	//call opendir with the path of the desired driectory
	current_dir = opendir(".");
	if (current_dir == NULL)
		return (0);
	//this will list all the files and subdirectories in our
	//opened dir
	while ((de = readdir(current_dir)) != NULL)
		printf("%s\n", de->d_name); //accessubg tge directory entry
		//struct to get the name of sub directory members
	closedir(current_dir);
	return (0);
}



/***
refs and declartion of the GNU manual
struct dirent {
    ino_t          d_ino;       /* inode number *
    off_t          d_off;       /* offset to the next dirent /
    unsigned short d_reclen;    /* length of this record 
    unsigned char  d_type;      /* type of file; not supported
                                   by all file system types 
    char           d_name[256]; /* filename 
};


***/
strerror:
used to print the corrosponding error message of the erronum
/*---------------------------------------------------*/
perror:
used to print the corrosponding error message of the erronum
example :

int fd = open("alice.txt", O_RDONLY);
if (fd == -1)
	perror("open");
/*---------------------------------------------------*/
/*---------------------------------------------------*/

exit:
-----
exit a process with desired status code;
lik:
exit(1); //you can specify in case of failure
exit(0); //in case of success
/*---------------------------------------------------*/
dup
/*---------------------------------------------------*/
dup2:
-----
change file descriptor to our desired one, which means we can redirect STDOUT to another file
so we can make pipes and output to other file 

example:
--------
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
int x = 1;

int main ()
{
	int	pid;
	int	fd;
	char *path = "/usr/bin/top";
	char *args[] = {"top", NULL};
	char *env[] = {NULL};
	
	printf("before forking parent %d\n\n\n", getpid());
	fd = open("trialfile.txt", O_RDWR | O_CREAT);
	if (fd == -1)
		perror("open");
	//redirecting the output from the STDOUT to trialfile.txt
	 dup2(fd ,1);
	//dup2(1, 1);
	pid = fork();
	if (pid == 0)
	{

		if (execve(path , args, NULL) == -1)
			perror("execve");
		return (0); 
	}
	else 
	{
		sleep(1);
		//send CTR-C signal after sleeping one second to close the program
		kill(pid, SIGKILL);
		wait(NULL);
	}
}

/*---------------------------------------------------*/
execve:
What is the use?
Executes command.
How?
#include <unistd.h>

     int
     execve(const char *path, char *const argv[], char *const envp[]);

execve("/usr/bin/cat",
		{
		"cat" ,
		"file.txt", 
		"-e", 
		NULL
		}, 
		{"NEW_ENV_VAR=newvar", NULL}
		)

example:
#include <unistd.h>
#include <stdio.h>

int main()
{
	//path of the executable
	char *cmd = "/bin/ls";
	//list of arguments, start with the name or path of the executable
	char *args[] = {"ls", "-la", NULL};
	//list of the environment variable, you can assign here, NULL terminated list
	char *env[] = {NULL};
	//executing the command
	execve(cmd, args, env);
	//if successful, it should close the program, otherwise it failed execution
	printf("if you see this, it means the execution failed\n");
	return (0);
}


Ref:
- man
- https://www.youtube.com/watch?v=Wtd-8OiZOjk  write your own shell

/*---------------------------------------------------*/
1- readline:
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char * readline (const char *prompt);

Read line from the terminal  and return it using prompt, the new line removed 
only the text of the line remained
if line is empty or reached the EOF return (NULL);
N.B:you must free() the return line after using it.
Compile with: -lreadline
example :
/*---------------------------------------------------*/
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
output: 
minishel tester $>  echo hello 
 echo hello 
minishel tester $> 

/*---------------------------------------------------*/
add_history:
Saves the readed line, (as readline() replace the readed line every new call )
add_history(line);

Take care to not to save empty lines in the history as it has no use, and will make
retrieving commands from the history unpleasent experience
Example:
--------
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
	//saved it to a then adding it to history
	add_history(a);
	//then print it back to the user 
	printf("%s\n", a);
	free(a);
	}
}

I don't know how to retriev the history's logs yet.

/*---------------------------------------------------*/
rl_on_new_line:
int rl_on_new_line (void)
Tell the update functions that we have
moved onto a new (empty) line, usually after ouputting a 
newline.
?????????

rl_replace_line  
rl_clear_history
rl_redisplay

(((All those fucntions above for handling the CTR-C part, will be used once or 
Twice, no need to spend much time on it now, ask later during the day inshalla)))


/*---------------------------------------------------*/
access:
#include <unistd.h>

int access(const char *path, int amode);
What it does?
Check the existance of a file and check the allowed permission.
how?
give:
const char *path = "/path/to/the/desired/file";
int amode = W_OK 	check the writing permission
			R_OK 	check the reading permission
			X_OK	check the execution permission, gives success if the user has privilage
			to execute the file even if the file doesn't has executino permission.  '
			F_OK 	check for the file existance
return value? 0 upon_success : else -1;
and erronum change according to the kind of the error 

example:
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int access(const char *path, int amode);
int main()
{
	char	*a ;
	int		found_executable;

	while (1)
	{
		//prompt the user for input with the message below
		a = readline("minishel tester $> ");
		//check if the file exists and has execution permission
		found_executable = access(a, X_OK);

		if (found_executable == 0)
			printf("Found %s and I can execute\n", a);
		else
		{
			//if not found check the existance of the file 
			//you can check ERRNOM for [ENOENT] intead of this condition
			found_executable = access(a, F_OK);
			if (!found_executable)
				printf("the %s exist but you are not allowed to execute it\n", a);
			else
				printf("File %s doesn't exist\n", a);
		}
		//saved it to a
		//then print it back to the user 
		// printf("%s\n", a);
		add_history(a);
		free(a);
	}
}
/*---------------------------------------------------*/
fork:
https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
proceeses in C playlist 
pid_t	fork(void);
separate the execution of the main in to two proceeses, child and assign 0 to it, then
the parent with the same process ID,
N.B: child process is copy from the main process, which means that memory is not shared
so don't be confused by variables that will have the same names inside the child.  '
example:
--------
#include <unistd.h>
#include <stdio.h>

int main()
{
	int	pid;
	printf("Inside main the original PID = %d\n", getpid());
	//fork() will separate the program execution into 2 proccesses 
	//child assigning 0 to it and parent with the same process id.
	pid = fork();
	if (pid == 0)
	{
		printf("Inside child process, getpid(pid) = %d, pid = %d, parent = %d\n",
		getpid(), pid, getppid());
	}
	else
		printf("Inside parent process,  getpid(pid) = %d, pid = %d parent = %d\n",
		getpid(), pid, getppid());
}
/*---------------------------------------------------*/
wait:
----
wait()
What do wait do?
Well it does what it said, it waits for the other process to finish
execution then execute the code in it's current process as follows.
'example:
#include <unistd.h>
#include <stdio.h>

/*creating program that prints from 1 to 10 using fork()*/
int main()
{
	int	pid;
	int	n;
	int	i = 0;

	pid = fork();
	if (pid == 0)
	{
		n = 1;
	}
	else
	{
		n = 6;
	}
	while (i < 5)
	{
		printf("%d ", n + i);
		i++;
	}
	
}
//Without using wait() the output is mixed up as follows
> 6 7 8 9 10 1 2 3 4 5 %     
//let's see the power of using wait in controlling the execution of the proccesses
#include <unistd.h>
#include<sys/wait.h>
#include <stdio.h>

/*creating program that prints from 1 to 10 using fork()*/
int main()
{
	int	pid;
	int	n;
	int	i = 0;

	pid = fork();
	if (pid == 0)
	{
		n = 1;
	}
	else
	{
		n = 6;
		//waiting for the child process to finish 
		//execution first
		wait(NULL);
	}
	while (i < 5)
	{
		printf("%d ", n + i);
		i++;
	}
	//printing new line after the end of the parent process
	if (pid != 0)
		printf("\n");

}
//Luckly we got the desired output with wait()
> 1 2 3 4 5 6 7 8 9 10 %       

wait upon successful termination of child process return the pid of the child
otherwise it returns -1
/*---------------------------------------------------*/
waitpid
wait for a specific process using it's ID'
wait(pid, NULL, 0);
/*---------------------------------------------------*/
wait3
wait4

Like wait and waitpid, but return analytics about the waited process, 
Like CPU usage, memory ....
/*---------------------------------------------------*/

pipe
-----
pipe(int *fd);
What is the use?
Transfer data between processes by writing data on one end and read 
data from other end o the pipe, (by pipe ends I mean files )
How?
It open 2 files descriptor one for writing and one for reading
fd[0] for reading
fd[1] for writing
remeber to close the fd that you don't use, before the code, then
close the fd you use inside desired process right after using it.'

example:
------------
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int	pid;
	int fd[2];
	int x;
	int y;

	printf("Inside main the original PID = %d\n", getpid());

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		x = 3;
		write (fd[1], &x, 4);
		printf("Inside child process, getpid(pid) = %d, pid = %d, parent = %d\n",
		getpid(), pid, getppid());
		printf("in child y = %d\n", y);
		close(fd[1]);
	}
	else
	{
		wait (NULL);
		close(fd[1]);
		read(fd[0], &y, 4);
		close(fd[1]);
		printf("Inside parent process,  getpid(pid) = %d, pid = %d parent = %d\n",
		getpid(), pid, getppid());
	}
	if (pid != 0)
		printf("y i s %d\n", y);
}
/*---------------------------------------------------*/
printf
malloc
free
write
read: 
read and write use system calls to perform the read and write.

/*---------------------------------------------------*/
close
open:
-----
#include <fcntl.h> 
stands for file control --->this library do system call to make file manipultations






/*---------------------------------------------------*/
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs:
All this family used to put cursus in specific place in the terminal,
which I believe will have no use in the program.

Below is an example that I don't understand. ':
//ref: https://www.scosales.com/ta/kb/106065.html
          Below is a sample program that will demonstrate the use of the 
           termcap functions tgetstr(), tgoto(), tgetent(), and tputs().  
           These functions are described in the SCO XENIX System V Development 
           System manual under termcap(S). 

           To compile:  Save this file as tcput.c.
                         Then  " cc  tcput.c  -ltermcap  -o tcput"

-----------------Cut Here-----------------------------------------------------
/*
 *
 *         This program places the cursor on the specified row and column.
 *         Rows and columns start at 0 from the top left hand corner.
 *         By default this program reads the TERM variable from the user's
 *         environment. If the Command line includes a terminal name, it will
 *         use argv[1] as the terminal type.  SCO suggests that you read the
 *      man page entry, line by line, and compare it to the program.
 *
 *     Command Syntax  ...    progname  [ TERM_type ]  Row  Col  <Return>
 *
 */

/*
#include<stdio.h>
#include<termio.h>  Note:  tcap.h includes stdio.h and termio.h
                              If you have SCO XENIX Development System 
                              Release 2.3, please look on page 7-6 and
                              7-7 of the C Library Guide.
*/

#include<tcap.h>
#include<errno.h>

#define MAXTERM 1024
#define MAXENTRY 512

char *BC;
char *UP;
char PC; 
short ospeed;

main(argc,argv)
int argc;
char *argv[];
{
         char * tgetstr();
         char * tgoto();
         static void outc();

         char termbuffer[MAXTERM];
         char cap_buf[MAXENTRY], *table;
         char type_term[10];
         char *PCstr;
         char *CL, *CM;
         struct termio oldterm, newterm;

         ioctl( stdout, TCGETA, &oldterm);
         ospeed = oldterm.c_cflag & CBAUD;
         newterm = oldterm;
         newterm.c_oflag = newterm.c_oflag  & ~(TABDLY);
         ioctl( stdout, TCSETA, &newterm);
         if ( argc == 3 )
                  strcpy(type_term, getenv("TERM="));
         else
                  strcpy(type_term, argv[1]);
         if( tgetent(termbuffer, type_term) != 1) {
                  perror("No termcap, fail");
                  exit(1);
         }
         table = cap_buf;
         BC = tgetstr("bc",&table);
         CL = tgetstr("cl",&table);
         CM = tgetstr("cm",&table);
         UP = tgetstr("up",&table);
         PCstr = tgetstr("pc",&table);
         if ( PCstr != NULL)
                  PC = PCstr[0];
         else
                  PC = '\0';
/*                              */
/*         CLEAR SCREEN       */
/*         tputs(CL,1,outc);  */
/*
 *                                      dest col      dest row
 */
         if ( argc == 3 )
                  tputs(tgoto(CM,atoi(argv[2]),atoi(argv[1])),1,outc);
         else
                  tputs(tgoto(CM,atoi(argv[3]),atoi(argv[2])),1,outc);
         ioctl( stdout, TCSETA, &oldterm);
         return(0);
}

static void outc(ch)
char ch;
{
         putchar(ch);
}

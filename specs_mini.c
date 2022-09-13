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
10- Handle environment variables, should expand to thier values ($IAM_A_VARIABLE)
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
readline
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
printf
malloc
free
write
access
open
read
close
fork
wait
waitpid
wait3
wait4
signal
sigaction
sigemptyset
sigaddset
kill
exit
getcwd
chdir
stat
lstat
fstat
unlink
execve
dup
dup2
pipe
opendir
readdir
closedir
strerror
perror
isatty
ttyname
ttyslot
ioctl
getenv
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs

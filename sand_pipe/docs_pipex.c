Bism Ellah El Rahman Elraheem 
Actual start date 25th July 
#this is documentation for implementing pipex project 



/*Allowed functions notes*/

open 
close
read
write,
malloc, 
free, 
perror
strerror
access
dup
dup2
execve 
exit
fork
pipe
unlink 
wait
waitpid

/*cases to be handled*/
1- giving arugments that contaisn " / ' like awk and grep "
2- taking /bin/ls full path as argument instead of the name of the command itself 
3- Don't know how many argv[] that I am going to break dwon for the argVec[] ={} 
4- How to search for the executable path through programming 
5- Memory allocation fro everything 

/*Implementation notes*/
1- Try to execute one command (Done)
2- execute commands by searching the path for the executable  (get your hands dirty with the execve) 
3- execute command through input file not the stdin 
4- out put the out put on the screen
5- parse and do everything of splitting the input
6- search for the executable 
7- handle the " ' /
8- handle argument that takes many parameters ex : "grep -C 4 "Hello \" workd\""
9- Try the process 
10- Talk to the other process, sending hello world string 
11- send the output through a pipe as input , by changing the input file of the other program through dup2()
12- Execute the other pipe with the same proram executed in the first 10 steps 
13- Stress test your program 



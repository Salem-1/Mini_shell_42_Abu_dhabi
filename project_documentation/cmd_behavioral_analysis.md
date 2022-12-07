this is behavioural analysis for cmds

#execve:
------
1- Take the env_variables from the main
2- Store it in a linked list as a copy
3- copy it to the export list 
4- Check if it's relative or absoloute path.
5- If absolout execute it on spot with execve
6- Else  search the PATH for the existance of the executable 
5- when you found it execute it with execve
6- Update the env with your export when needed: 
	
	cd : update PWD , OLD_PWD 
	sh || ./minishel : update SHL_LEVL if reached 100 reset to 1




#export:
-------
					consider doing export as Global_variable
usage:
Save variables to the envirnment 
cases:
	
	export x=1

saves x=1 as variable in export and env

	export x =1
	error
	
	export x= 1   error 
Display export varibales in specific format,
 which include all environment variables + declared variables without value
	
	export 
		 
for example:

	declare -x COLORTERM="truecolor"

if the variable has a value it save it and assign it to the environment variables
export x      save x in the export list, but not displayed when calling env 
if x exists and has value, it do nothing
export x=1 y=2 z=3   save x, y and z (can take many arguments),
			take it as string then split,
			save it 
			free it
export x=3    save x=3
export x+=3     save x=33   add items as strings (export save stuff as strings)
export 3x=2     error,  functions must start with alpha use isalpha()
unset:
------
unset x   clear the x from the export list and free it
unset x, y, z  removes x, y and z from export list can take many arguments

#8th Oct:
inshalla
-Fix redirection for outliar cases 
    echo hi > file.txt hello how this is appended to the file.txt file
-do the append >>
-do the input
-fix norminette
-fix leaks
-do the exit codes and print error to 2
-do the dollar expansions
-do the heredoc
-test and fix all over again
-test for outliar cases
-submit and celebrate inshalla 


# the output >
	echo hi > file.txt
create flie.txt and fill it with h

	>
	zsh: parse error near `\n'                                      '
-
	echo hi >
	zsh: parse error near `\n' 
-

	echo > ""
	zsh: no such file or directory:


	"" > file.txt
	zsh: permission denied:

	hello > file.txt
	zsh: command not found: hello

	echo hi > file.txt > file2
create file.txt as empty file  then creates file2 and fiil it with hi

	file.txt > file2
	zsh: command not found: file.txt

	bash-3.2$ cat file.txt
	hi
	bash-3.2$ echo hi >> file2 >> file.txt
	bash-3.2$ cat file.txt
	hi
	hi

Outliar cases:

Create file.txt and put in it echo hello hi
	
	echo hi > file.txt hello ho

Creates the file.txt and put the echo cmd output inside it
	
	>file.txt echo is this going to be printed
	cat file.txt
	is this going to be printed

# The input <

Execute the command before the < taking the file name after teh < as an input

	cat < file.txt
	s this going to be printed

Take file.txt as input file for cat

	< file.txt cat
	this is the content of file.txt

In the case below the shell tries to execute file2.txt and failes as this is not a command, so the executble must be right after first file name

	< file.txt file2.txt cat
	bash: file2.txt: command not found

Outliar case

	< file.txt cat file2.txt
	file2 content

Ignore file.txt, then cat takes file2.txt and file3.txt as argument and executes normally 

	< file.txt cat file2.txt file3.txt
	file2 content
	file3 content

Ignore file.txt and use the f2, f3, f4, ....
	cat < file.txt f2  f3 f4
	f2
	f3
	f4

if nothing after the input < , then throw an error

	cat <
	bash: syntax error near unexpected token `newline'


# << heredoc



Giving command then delimeter after the <<, will read and save all what you write waiting to type delimiter in one line, then will give all what you written as argument to the command before the <<

	cat << deli
	heredoc> this is firlst line
	heredoc> seconde line to be read by cat
	heredoc> deli
	this is firlst line
	seconde line to be read by cat


Giving command without delimiter throw an error

	cat <<
	zsh: parse error near `\n'


when do cd,  export arg, unset    execute and when they dont

	Do execute 				|			Dont execute
	export a > create_file	|  export a < invalid file
	export b << deli		|  export c > f1 >f2 < invalid_f
	export d				| export d > f | command 

#Summary:

executed:

	1-Alone
	2-in output mode, successful
	3-in invalid input
not execute:
	1-pipes
	2-Unsuccesful redirections

execve:
------
1- Take the env_variables from the main
2- Store it in a linked list as a copy
3- copy it to the export list 
4- Check if it's relative or absoloute path.'
5- If absolout execute it on spot with execve
6- Else  search the PATH for the existance of the executable 
5- when you found it execute it with execve
6- Update the env with your export when needed: 
	cd : update PWD , OLD_PWD 
	sh || ./minishel : update SHL_LEVL if reached 100 reset to 1




export:
-------
					consider doing export as Global_variable
usage:
Save variables to the envirnment 
cases:
export x=1    saves x=1 as variable in export and env
export x =1   error
export x= 1   error 
export        Display export varibales in specific format,
		 which include all environment variables + declared variables without value 
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

25th Sept.:
    upon piping |:
        -the prompt disappear after execution (solved, I forgot to put i = 0; before entering the wait(NULL) loop, in exec multiple pipes file)
        -if given 2nd wrong command it gives an infinite while loop of prompt that take itself as command then print (pending)


27th sept:
    -when export through an error the prompt don't execute any commands
    -Do the exit status for wrong export

3rd Oct:
	-CTR C doesn't interrupt infinite loop operation
	-When one command hang, I had the prompt but it doesn't implement any commands
4th Oct:
	should I save the double and single quotes with the command or no?
	I believe no
	fix it in the morning inshalla
	then do the redirections
	fill the cmds list
	then try the redirections 
	then the heredoc
	then the extreme cases
	then expansion of the $ and ? 
	inshalla 

	-minishell $> hi||
		~hi~
		~|~
		~|~
		~|~
		~|~
		~hi|~
		~|~
		~|~
		~hi||~

	-minishell $> dskcj 
		flag =  arg = ~~,
		flag = c arg = ~dskcj~,
		flag = c arg = ~dskcj ~,
		n_cmds = 2
	-minishell $> dskcj| 
		inside smasher cmd[5] = (|)
		flag =  arg = ~~,
		flag = c arg = ~dskcj~,
		flag = p arg = ~|~,
		flag = c arg = ~| ~,
		n_cmds = 3
	-minishell $> dskcj|
		inside smasher cmd[5] = (|)
		flag =  arg = ~~,
		flag = c arg = ~dskcj~,
		flag = p arg = ~|~,
		n_cmds = 3
	-minishell $> dskcj|
		inside smasher cmd[5] = (|)
		flag =  arg = ~~,
		flag = c arg = ~dskcj~,
		flag = p arg = ~|~,
		n_cmds = 3
echo hi >> l lslsls
bash-3.2$ echo hi >> l lslsls 
bash-3.2$ cat l
hi lslsls
hi lslsls
hi lslsls

8th Oct:
	the outliar redirection:
	ahsalem@lab3r3s12 sand_box_shell % >file.txt echo is this going to be printed
	ahsalem@lab3r3s12 sand_box_shell % cat file.txt
	is this going to be printed

9th Oct:
	./minishell
	minishell: ./minishell: command not found
	
	if nothing after the input < , then throw an error

	cat <
	bash: syntax error near unexpected token `newline'


	bash-3.2$ | hi
	bash: syntax error near unexpected token `|'
	bash-3.2$ > hi
	bash-3.2$ < hi
	bash-3.2$ 

	ls | < f cat
	gives segfault

10th Oct:
	remember to check the bash maximum buff size for handling large lines
	exit dont exit
	and other builtins are mulfunctioned

15th Oct:
    cat main.c | grep ah 
    give an infinite loop or opened file            ------------------> I doubt the t_pipes filling part caused of throw parse error

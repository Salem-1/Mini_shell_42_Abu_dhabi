I would like to thank Gerard  for providing me with this amazing testing document
Github : gkintana

bash-3.2$ ls | echo hi > file.txt < cd
bash: cd: No such file or directory

	>
	bash: syntax error near unexpected token `newline'

	>>
	bash: syntax error near unexpected token `newline'
	
	>>>
	
	>>>>
	>>>>>
	>>>>>>>>>>>>>

	>|
	>>|
	>>>|
	>>>>|
	>>>>>|
	>>>>>>>>>>>>>|

	|>
	|>|>|>|>|>|>|>|>
	|>>
	|>>|>>|>>|>>|>>
	|>>>
	|>>>>
	|> > > >>> > >> > >>

	>||>
	> | | >

	>|>
	>>|>>
	>|>>
	>|>>>
	>>>|>>>
	>>>>|>>>>

	>ls
	>>ls
	>>>ls
	>>>>ls
	>>>>>ls
	>>>>>>>ls
	>>>>>>> ls

	>|ls
	>>|ls
	>>>|ls
	>>>>|ls

	"ls
	"           ls
	'ls
	'           ls
	"ls"
	'ls'
	"ls            "
	"           ls"
	"           ls            "
	'ls            '
	'           ls'
	'           ls            '

	"hello world"test" "
	"hello world"test" """asd
	"hello world"test" """ asd
	"hello world" test ""
	'asdasdsa ' a sd as
	"helloas d a ad  d sadda"2 as d a "asd" "asd" sad's'
	echo "helloas d a ad  n       d sadda"2                  as d a"asd" "asd" sad's'

	echo ./minishell >> 1 > 2>>file3 | grep 123

	65 5 464  5>> A>D>SA>>1
	"ASD"AS" "AS"D "A""
	"AS"D"AS"DAS"SDA"SD"" asda a d as
	     asDA >A>SD>DS>D Sasd 123 <ASDA<A<D<<D asd asd"123"123""ads  "asd"
	asdlasldsalasdladslasdlasd asdas das dsasdsd asdsd d sd d s ""asd asdas s
	asdlsd asdas das dsasdsd asdsd d sd d s  ""  asdas 123

	hello"test"
	hello"test"123
hello "test"123
hello"test" 123
"hello"test" 123"123 123 123

A"D"ASDDAS"D"
A "D"AS DDAS"D"
A"D"ASDDAS" D"

echo hello |          |123
echo hello |123
echo hello || 123
echo hello >|123
asd|>|asd

https://unix.stackexchange.com/questions/45201/bash-what-does-do
>|asd

asda> |asd>asd
asd>asd | | >asd
asdas |ASD dasas
asdas |>ASD dasas
asdas |">ASD" dasas
echo"hello" >asd
echo "hello">asd
echo "hello" >asd

"h el  lo"|"t e st"
"hello"|"test"
"hello""test"
hello"test"""
hello"test"""asd  123 21 3  123
hello"test""asd  123 21" 3 123
test"123"aSDA" " 123

echo "hello"test"ls"
echo "hello"test "ls"
echo "hello"test"" ls
echo "hello"asd"" 123 12 3 213
echo "hello"test"" asd123 1 321
echo "hello"test" " asd123 1 321
echo "hello"te st" " asd123 1 321

D S A>D>ASD >DS"A"DAS""SD|SAD|"AS|'|||''D"|SD|SDS|D
D S A>D>ASD >DS"A"DAS""SD|SAD|"AS|'|"|''D""|SD|SDS|D
D S A>D>ASD >DS"A"DAS""SD|SAD|ASD|SD|SDS|D
echo D S A>D>ASD >DS"A"DAS""SD|>asd
echo D S A>D>ASD"" >DSADASSD|>asd
echo D S A>D>ASD"""">DSADASSD|>asd
echo D S A>D>ASD"""">DSADAS""SD|>asd
asd|>adAS>DAS>"SD">SADasd
lsa >ASD ASD>'>SD' AD DD A|D |AS A" SA"D"AS"D SA>DA>SD<AS<D A<SD
A>SDA>SD>AD>>ASD>ASA<SD<AS<DAS<D<AS ASDasdasd asd as d asd A|SD|ASD|ASD|AS|asd

echo hello > ASD"'123'"
A|A|DD|S|S|AA|
ls|echo|ls|echo|ls|echo|ls|echo|ls|echo|ls
ls|echo|ls|echo|ls|echo|ls|ec"h"o""|ls|echo|"ls"
ls|echo|"ls"|"echo"|'ls'|echo|ls""a|ec"h"o""|ls|echo|"ls"
ls|echo|"ls"|"echo"|'ls'|echo|ls""|ec"h"o"""|ls|echo""a|"ls""

asdas |">ASD" ""| dasas
asd"as" |">ASD"| das|"as"
asd'as' |'>ASD'| das|'as'
asd"as" |>ASD| das|"as"

echo hello ">" file one
echo hello > file one
echo hello 123 <> hello				(works in bash, prevented it in our project)
echo hello 123 >< hello
echo hello 123 <|> hello
echo hello 123 >|< hello

hello'te"s"t'				= hellote"s"t
hello'te"st'				= hellote"st
hello"test'"				= hellotest'
hello"'t"est"''"''			= hello'test''
hello'"t'est'""'""			= hello"test""
hell''o"""tes't"			= hellotes't
hell''o"""""tes't"			= hellotes't
hello'te"s"t"asd"asd'		= hellote"s"t"asd"asd

"AS"D"AS"DAS"SDA''"''SD"" a's'da a d 'as'
'AS'D'AS'DAS'SDA""'""SD'' a"s"da a d "as"
'asdas 'sda ' das asd' aS D DAS"D SA"A SD""
ASDS"DAD"A"A"SA"S'ds'ads'sd'sd''" asds sad  dsa
""ASDS"DAD"A"""A"SA"S'ds'''''''ads'sd'sd''""" asds s"a'd"  132
A"SD"AS"DD"ASD"ASD"ASADS""''asd'a'ss'da'"s"aasd

echo $USER
echo $US ER
echo $ US ER
echo '$USER'
echo '$US ER'
echo '$ USER'
echo "$US ER"
echo "$ US ER"
echo aasdasd$$'$'$$USER""123 123 123
echo AD"AS"DAS"D"AS"DAS"D"asd" 'a""d'a'sd'"as'd'as'''''"

echo a'sd'$$$$USER
echo a'sd'$$$$$USER
echo 'a""d'a'sd'"as'd'as'''''      " | cat -e asd as da sd
asd asd as d asd  AS>D A>SD>AS> DSA>SD>asd			(INVALID READ)


Note: results are different on mac :(
						Linux				Mac
ls > 'A"asd"'           = 'A"asd"'			= A"asd"	
ls > 'A'                = A					= A
ls > 'A'"asd"           = Aasd				= Aasd
ls > "A"'asd""'         = 'Aasd""'			= Aasd""
ls > A'asd""'           = 'Aasd""'			= Aasd""
ls > 12"3"''123         = 123123			= 123123
ls > "123"              = 123				= 123
ls > "'123'"            = "'123'"			= '123'
ls > '"123"'            = '"123"'			= "123"
ls > "A"'asd""'"123"    = 'Aasd""123'		= Aasd""123
ls > "123'"1""          = "123'1"			= 123'1
ls > "123'"""           = "123'"			= 123'
ls >'S>D'               = 'S>D'				= S>D
ls > '>SD'              = '>SD'				= >SD
ls > 'SD'               = SD				= SD
ls >" A>>sd"            = ' A>>sd'			=  A>>sd
ls >"A>>s'd"            = 'A>>sd'			= A>>s'd
ls >'12"3'              = '12"3'			= 12"3
ls >'1>2"3'             = '1>2"3'			= 1>2"3
ls >'1>>2"3'            = '1>>2"3'			= 1>>2"3	(INVALID READ)
>"">>>>asd								(INVALID READ)

ls >'>>file'
ls >">>>>file"
ls -la > file1 > '>file2' > file3
ls -la > file1 > '>file2' > file3 << "<file4" < '>file5'


Simon tester

echo $PWD
echo '$PWD'
echo "$PWD"
echo $'PWD'				(INVALID READ)
echo $"PWD"
echo $PWD$USER
echo $PWD"$USER"
echo "$PWD"'$USER'
echo "$PWD"'$USER'123
echo $PWD123"$USER"
echo $PWDasd$USER
echo 123 $PWDasd $USER
echo $USER'$USER'
echo $USER'   $USER'
echo $USER'123'
echo $USER'123'echo $USER'123'		(INVALID READ)
echo $USER"123"
echo $USER$123
echo $USER"$123"
echo $USER'$123'
echo "$US'ER"				(INVALID READ)
echo $U>SER">123"
echo $SA$SA$SA$SA$AS$S$SA$USER$S$SA$S$SA$S$AAS$USER
echo '""""""""$USER""""""""'


echo "'$USER'"
echo "''"
echo "'$USER'" "" '' $USER $USERr '"$USER"'
echo $=$=$= $=  $=
echo $+$+$+  $
echo -n
echo $
echo '$>'
echo '$'
echo '$'123
echo "$"
echo "$"asd
echo $?
echo '$?'
echo "$?"
echo $USER
echo "$USER"
echo "'$USER'"
echo " '$USER' "
echo text"$USER"
echo text"'$USER'" ' $USER '
echo "text"   "$USER"    "$USER"
echo '              $USER          '
echo               text "$USER"            "$USER"text
echo ''''''''''$USER''''''''''
echo """"""""$USER""""""""
echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''
echo $USER '' $USER $USER '' $USER '' $USER -n $USER
echo "$USER""$USER""$USER"
echo text"$USER"test					(INVALID READ)
echo '$USER' "$USER" "text \' text"
echo '$USER'
echo $USER " "
echo "$USER""Users/$USER/file""'$USER'"'$USER'
echo "$USER$USER$USER"
echo '$USER'"$USER"'$USER'
echo '"$USER"''$USER'"""$USER"
echo " $USER  "'$PWD'
echo " $USER  \$ "'$PWD'
echo $USER=4
echo $USER=thallard
echo $USER
echo $?
echo $USER213
echo $USER$12USER$USER=4$USER12
echo $USER $123456789USER $USER123456789
echo $USER $9999USER $8888USER $7777USER
echo $USER $USER9999 $USER8888 $USER7777
echo $USER $USER9999 $USER8888 $USER7777 "$USER"
echo "$USER=12$USER"
echo "$9USER" "'$USER=12$SOMETHING'"
echo '$9USER' "'$USER=12$SOMETHING'"
echo '$9USER' '"$USER=12$SOMETHING"'
echo '$9USER' '"'$USER=12$SOMETHING'"'
echo $PWD/file
echo "$PWD/file"
echo "text" "text$USER" ... "$USER"
echo $PWD
echo "$US'ER"$PWD

echo $LS_COLORS$LS_COLORS$LS_COLORS$LS_COLORS$LS_COLORS$LS_COLORS$LS_COLORS
echo $!
echo '$!'
echo "$!"
echo $@
echo '$@'
echo "$@"
echo $#
echo '$#'
echo "$#"
echo $$
echo '$$'
echo "$$"
echo $%
echo '$%'
echo "$%"
echo $^
echo '$^'
echo "$^"
echo $&
echo '$&'
echo "$&"
echo $*
echo '$*'
echo "$*"
echo $(
echo '$('
echo "$("
echo $)
echo '$)'
echo "$)"
echo $-
echo '$-'
echo "$-"
echo $+
echo '$+'
echo "$+"
echo $=
echo '$='
echo "$="
echo $[
echo '$['
echo "$["
echo $]
echo '$]'
echo "$]"
echo ${
echo '${'
echo "${"
echo $}
echo '$}'
echo "$}"
echo $<
echo '$<'
echo "$<"
echo $>
echo '$>'
echo "$>"
echo $.
echo '$.'
echo "$."
echo $/
echo '$/'
echo "$/"
echo $\
echo '$\'
echo "$\"
echo $~
echo '$~'
echo "$~"
echo $`
echo '$`'
echo "$`"
echo $;
echo '$;'
echo "$;"

cd
cd ~
cd .
cd -
cd ///////

Dale's Test
{
	mkdir test
	cd test
	rm -rf ../test
	pwd
	cd ..
	cd $OLDPWD

	export s="s -a"
	l$s"l"

	echo $PWD#$PWD:$PWD,$PWD{$PWD
}

Nart's Test
{
	env -i ./minishell		(Should not segfault)
}

Radi's Test
{
	./minishell | ./minishell | ./minishell
}

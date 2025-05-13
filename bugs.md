## Tester feedback:

1. while validating the token list, also validate brackets
4. cd followed by blank needs to use $HOME env var
5. "unset TES\T" leads to syntax error. quote removal function?
6. export needs to return exit code 1 for bad inputs, like TES!T=123
7. whatever changes made to export also apply to unset
8. exit needs to return the exit status provided as argument, and that argument needs to be checked for valid input (no negatives, no alpha, etc)'

## Built-in bugs:
1. exit 0 0: segfaults, also exit code should be 1
2. exit -1: code should be 255
3. exit wrong, exit --0: exit code is 2 because arg is NaN
4. env | grep "_=": bash returns _=/usr/bin/env, what should minishell return?
5. 

## Stupid edge cases:
..
- should have exit code 127, but instead gives exit code 126.

echo aaa "" | cat -e
- should print a space after aaa

ls|cat Makefile|cat<<asd>out
'$USER'
- parameter substitution in heredoc happens even if in quotes...

/bin/echo 42 > tmp_redir_out 42
- tester says stdout is wrong compared to bash, but I can't see why. Looks correct afaik

/bin/echo 42 > /dev/null > /dev/null > /dev/null > /dev/null > tmp_redir_out
- same thing, stdout wrong. No idea why, looks good to me

/bin/env | grep "_="

cd "$H"O"ME"/Desktop/
echo $?
echo $?
- typing echo $? twice doesn't change second exit code to 0

/$NOVAR
- behaves weirdly, need to investigate

'''''''''''''''' echo ok
- should treat '' as a command

echo $/ $/ 
- should output $/ $/

## Tester links
https://github.com/zstenger93/42_minishell_tester
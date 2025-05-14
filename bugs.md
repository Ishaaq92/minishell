## Tester feedback:

1. while validating the token list, also validate brackets
4. cd followed by blank needs to use $HOME env var
5. "unset TES\T" leads to syntax error. quote removal function?
6. export needs to return exit code 1 for bad inputs, like TES!T=123
7. whatever changes made to export also apply to unset
8. unset doesn't seem to work at all atm
9. exit needs to return the exit status provided as argument, and that argument needs to be checked for valid input (no negatives, no alpha, etc)'
10. export test+=: do we need to support this bs

## Built-in bugs:
1. exit 0 0: segfaults, also exit code should be 1
2. exit -1: code should be 255
3. exit wrong, exit --0: exit code is 2 because arg is NaN
4. env | grep "_=": bash returns _=/usr/bin/env, what should minishell return?
5. echo strips whitespace in bash, but we can probably ignore this
6. should env list be sorted?

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


## Tester red ticks

### Parsing hell
- 11: echo missing space bug
- 12-15: heredoc
- 25-31: export again
- 43-58: more export
- 70-77: more export
- 89: export again
- 101: empty string being ignored and not treated as a command
- the rest: export and echo edge cases

### builtins
- 1: tests the ~ expansion, ignore it
- 47, 52: missing a space at the end
- 73: echo - prints nothing
- 122, 132: cd - segfaults, should print OLDPWD I think
- 123: no idea, works fine I think
- 124: cd echo echo should say too many args
- 128, 130-132: tests the ~ expansion, ignore it
- 140: tests an env option, ignore it
- 165, 170: ignore, filing it under unsupported
- 200: export +=...
- the rest: unset and exit bugs, mostly error codes

### Pipelines
- 15, 16: certain envs like '_=' and 'SHLVL' don't match bash exactly
- 25-30, 38-40: heredoc and pipes don't work well together

### Redirs
- 80-88: heredoc bugs, works fine in terminal but tester thinks its wrong

### SCMD
- 4: should exit 127 instead of 126
- 7: odd number of quotes, ignore it
- 26: should exit 127 instead of 126
- 28-31, 34: look up how ./ and / should be handled

### Variables
- 5-7, 13, 14: export bugs
- 41, 42: $PWD is not updated by cd
- 43 and the rest: export bugs

### Correction
- 2: should exit 127 instead of 126
- 19: exit "" should exit with 2 instead of 0
- 45: echo "" '' should print one space
- 82: export USER= is a valid command and should replace USER with a blank value
- 83-92: export is not working as intended
- 95, 96: unset errors
- 104: when cd'ing into a folder without permissions, match error output to bash
- 114: complex command, but I think its just the export that's not working

### Path fails
- unset problems

### syntax errors
- 8: the ~ expansion which we do not need to support
- 15, 16: should have exit code 127 instead of 126
- 20-22: working as intended through terminal, not working for tester only
- 40-43: it tests the 'noclobber' operator setting which isn't supported. Effectively, don't overwrite the file if it already exists

### Go wild section
- 10: how the bash command interacts with your tokens
- 12: unset is currently not working
- 13-15: env -i, we do not need to implement any options or args for env
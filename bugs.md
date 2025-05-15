## features left to implement

1. while validating the token list, also validate brackets
2. "unset TES\T" leads to syntax error. quote removal function?
3. export needs to return exit code 1 for bad inputs, like TES!T=123
4. whatever changes made to export also apply to unset
5. export test+=: do we need to support this
6. parameter substitution where a value has spaces in it needs to be split into separate tokens eg: export T="-n test1 -n test 2" echo $T
7. wildcard substitution

## Built-in bugs:
1. exit -1: code should be 255
2. exit wrong, exit --0: exit code is correctly set to 2, but you need to exit
3. echo strips whitespace in bash, but we can probably ignore this

## Stupid edge cases:
..
- should have exit code 127, but instead gives exit code 126.

ls|cat Makefile|cat<<asd>out
'$USER'
- parameter substitution in heredoc happens even if in quotes...

/$NOVAR
- behaves weirdly, need to investigate

'''''''''''''''' echo ok
- should treat '' as a command

echo $/ $/ 
- should output $/ $/

 echo wtf | > out
 - should put wtf in out, and not print an error

## Tester links
https://github.com/zstenger93/42_minishell_tester


## Tester red ticks

### Parsing hell
- 11: echo missing space bug
- 12-15: heredoc
- 25-31: export again
- 46: seems to be fine? export T=e E=c S=h L=o L=ok, $T$E$S$L
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
- 12: unset not accepting multiple arguments
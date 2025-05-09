## Tester feedback:

1. Execution breaks when a bad command name is given; stop forking and execve if a bad name is given
2. while validating the token list, also validate brackets
3. wrong exit codes: 139 for bad syntax (?), 127 for bad command name
4. make sure you're treating single and double quotes appropriately for parameter sub
5. cd followed by blank is incorrect > needs to go to $HOME right
6. cd followed by bad path needs to return exit code 1, and remove the "Bad Path" message
7. "echo oui | echo non | echo something | grep oui": this should return 1, not zero
8. "unset TES\T" leads to seg fault. Possibly due to quote removal?
9. export needs to return exit code 1 in a bunch of scenarios
10. exit needs to return the exit status provided as argument, and that argument needs to be checked for valid input (no negatives, no alpha, etc)
11. 


## Built-in bugs:
1. echo: the -n flag itself is being printed when it shouldn't
2. "echo -nn bonjour": should print "bonjour"(no newline)
3. "echo -n -n -n bonjour": should only print "bonjour"
4. 


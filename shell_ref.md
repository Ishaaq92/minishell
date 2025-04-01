https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

## Shell execution

1. read input
2. break input into tokens: words and operators
3. parse the input into simple commands and compound commands
4. perform expansions
5. perform redirection
6. execute functions, built-in or external
7. wait for command to complete and collect the exit status

## Quotes

Quotes remove the special meaning of certain characters or words. 

Single quotes preserve the literal value of each character within quotes.
A single-quote cannot occur within single-quotes, eg echo 'It's Shell Programming' 

double quotes work the same way, with the exception of **dollar sign, backtick, and backslash,** which are treated differently.

## Token recognition

shell reads inputs in terms of lines. The input lines are parsed using two modes: ordinary token recognition and processing of heredoc.

If a heredoc token is recognised, immediately start the heredoc processing after the new line token. 

When there is no heredoc, shell breaks inputs into takens by applying the first applicable rule beloew to the next character in its input. The token applies until it is no longer applicable. The characters forming the tokens are exactly as those in the input, including the quotes. If a token has no characters, it will continue to process until it reaches the end for a token.

Rules:
1. if end of input, current token is delimited (stopped, cut off)
2. if previous character was an operator and current character is not quoted and can be used with previous characters to form an operator, it becomes a part of that operator token
3. if previous character was an operator and the current one isn't, the operator is delimited
4. if character is backslash or quotes and its not quoted, it shall affect quoting for subsequent characters until the end of quoted text. Meaning, no substitutions are performed and characters inside the quotes are treated exactly as they are. The token is NOT delimited when it reaches the end of quoted field
5. if current character is dollarsign or backtick, the shell will attempt an expansion. The shell will read sufficient input to determine the end of the input to be expanded. While processing characters, if instances of expansions or quoting are found within the substitution, the shell will recursively process these appropriately. The token is NOT delimited after the end of substitution
6. if current character is not quoted and can be the start of a new operator, the current token is delimited, and the current character is used as the start of the next operator token
7. if current character is an unquoted blank, any token containing the previous character is delimited and the current character is discard
8. if the previous character was part of a word, the character character is appended to that word
9. if current character is #, it and all characters before the next newline are discarded as a comment. The newline that ends the line is not part of the comment
10. the current character is used as the start of a new word

Follow these rules to create tokens, THEN categorise them as required by Shell Grammar. 

## Alias substitution

after a token is delimited but before applying the grammar rules, determine if the word in it is a valid alias for a command.

## Reserverd words? Do we need to implement this?

## Word expansions?

## Redirection: to be continued...

### heredoc TODO

## Quoting

metacharacters: an unqouted character that separates words: space, tab, newline, |, &, ;, (, ), <, >. 

token: sequence of chars considered a single unit by the shell. It is either a word or an operator

escape char '\': preserves the literal value of the next character that follows, with the exception of enwline. If \newline happens, it is treated as line continuation (removed from input stream and effectively ignored).


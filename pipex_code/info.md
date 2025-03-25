## Usage

Pipex replicates the following shell command:

`< infile cmd1 | cmd2 > outfile`

- < redirects input to infile
- cmd1 is the first command
- | is the pipe, the output of cmd1 goes into cmd2 (even if its blank!)
- > redirects the output of cmd2 to outfile

To mimic the above command, do this:

`./pipex infile "cmd1" "cmd2" outfile`

## Here_doc

Pipex also supports >> and <<:

`cmd << LIMITER | cmd2 >> outfile`

- << switches input to standard input, keeps reading until it reads whatever is in LIMITER
- eg if LIMITER is "lim", the entire line has to only be lim
- >> works the same as >, except instead of overwriting the original file, it adds to it

## Examples

./pipex infile "head -n 5" "tail -n 1" outfile

./pipex infile "cat" "sleep 1" outfile

./pipex here_doc lim "cat" "head -n 3" outfile

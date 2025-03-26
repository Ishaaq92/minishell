## getcwd

`char *getcwd(char buf[.size], size_t size);`

returns the cwd as an absolute path into buf, which has length size.

If buf is NULL, the memory is allocated dynamically, if the size is zero then buf is allocated automatically.

Returns NULL on failure.

## chdir

`int chdir(const char *path);`

changes the current working directory of the calling process to the directory specified in path. 

returns zero on success, -1 on failure.


## stat, fstat, lstat

`int stat(const char *restrict pathname, struct stat *restrict statbuf);`
`int fstat(int fd, struct stat *statbuf);`
`int lstat(const char *restrict pathname, struct stat *restrict statbuf);`

return information abouta  file, in the buffer pointed to by statbuf. No permissions required on the file itself, but execute permission is required on directories that lead up to the file.

stat retrieves information about the file pointed to it.
lstat does the same but if its a symbolic link, it returns info on the link itself.
fstat is identical to stat, but the info on the file is specified with a file descriptor.

## unlink

`int unlink(const char *pathname);`

deletes a name from the filesystem. If the name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse. 

If a process has the file open, the file remains in existence until the last fd to it is closed. 

If it refers to a symlink, the link is removed. 

returns zero on success, -1 on failure.

## execve

`int execve(const char *pathname, char const **argv, char const **envp);`

executes the program referred to by pathname. The program currently running is replaced by the new program, with a new stack and heap.

does not return on success, -1 if error.

## dup, dup2

`#include <fcntl.h> /* Definition of O_* constants */`

`int dup(int oldfd); `
`int dup2(int oldfd, int newfd);`

dup allocates a new fd that refers to the same file as oldfd. After calling dup, the new and old fd can be used interchangeably. 

dup2 does the same but allows you to specify the new fd. If newfd was already open, it is closed and reused. 

returns new fd on success, -1 on error.

## pipe

`int pipe(int pipefd[2]);`

creates a oneway data channel used for interprocess communication. pipefd[2] is an int array that contains two fds referring to ends of the pipe. fd[0] is the read end, fd[1] is the write end. 

returns zero on success, -1 on error.

## opendir

`#include <sys/types.h>`
`#include <dirent.h>`

`DIR *opendir(const char *name);`

opens a dir stream corresponding to the parameter, and returns a point to the dir stream.

Returns NULL on error.

## readdir

`#include <dirent.h>`

`struct dirent *readdir(DIR *dirp);`

readdir() returns a pointer to a dirent struct representing the next directory entry in the dir stream.

Returns NULL  on reaching the end, or if an error occurred. 

The dirent struct looks like this:

struct dirent {
ino_t          d_ino;       /* Inode number */
off_t          d_off;       /* Not an offset; see below */
unsigned short d_reclen;    /* Length of this record */
unsigned char  d_type;      /* Type of file; not supported
								by all filesystem types */
char           d_name[256]; /* Null-terminated filename */
};

## closedir

`int closedir(DIR *dirp);`

closes the dir stream, and the underlying fd. 

returns -1 on error. 

## strerror

`#include <string.h>`

`char *strerror(int errnum);`

returns a pointer to a string describing the error code in errnum. 

Returns a blanket statement if error is unknown, the error description if a match is found. 

## perror

`#include <stdio.h>`
`#include <errno.h>`

`void perror(const char *s);`

produces a message on standard error describing the last error encountered. 

If s is not NULL, s is printed followed by a colon and the actual error message. 

The arg string should be the name of the function that incurred the error.

## isatty

`int isatty(int fd);`

tests whether fd is an open fd referring to a terminal.

returns 1 if it does, 0 otherwise.

## ttyname

`char *ttyname(int fd);`

returns a pointer to the null-terminated pathname of the terminal pointed to by fd. 

returns NULL on error.

## ttyslot

`int ttyslot(void);`

legacy function; returns index of the current user's entry in some file.

???

## ioctl

`#include <sys/ioctl.h>`

`int ioctl(int fd, unsigned long op, ...);  /* glibc, BSD */`

ioctl() manipulates the device parameters of special files (terminals).

The second arg is a device dependent op code. Third is a pointer to memory. 

## getenv

`#include <stdlib.h>`

`char *getenv(const char *name);`

searches the environment to find the environment variable name, and returns a pointer to its value.

returns NULL if there is no match.

## tcsetattr

`#include <termios.h>`

`int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p);`

sets the parameters associated with the terminal referred to by the arg fildes.

## tcgetattr

`#include <termios.h>`

`int tcgetattr(int fildes, struct termios *termios_p);`

gets the parameters associated with the terminal referred to by the arg fildes.

## tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

`#include <curses.h>`
`#include <term.h>`

`int tgetent(char *bp, const char *name);`
`int tgetflag(const char *id);`
`int tgetnum(const char *id);`
`char *tgetstr(const char *id, char **area);`
`char *tgoto(const char *cap, int col, int row);`
`int tputs(const char *str, int affcnt, int (*putc)(int));`


conversion aids for programs that use the termcap lib. 
they can only be used to query the capability of entries for which a terminfo entry has been compiled.

tgetent routine loads the entry for name. 

tgetnum gets numeric entry for id, -1 if not available.

tgetstr returns string entry for id, zero if not available. tputs is used to output the returned string.


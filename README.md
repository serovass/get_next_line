# get_next_line
A function that stores, in the parameter "line", a line that has been read from the given file descriptor

The function must be prototyped as follows: int get_next_line(int fd, char **line);

External functions: 
```
read
malloc
free
```

Compiled in this way: `gcc -Wall -Wextra -Werror -D BUFFER_SIZE=123 <files>.c`

The return value can be 1, 0 or -1 depending on whether a line has been read, 
when the reading has been completed (meaning read has returned 0), 
or if an error has happened respectively.

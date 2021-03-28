# gnl

The aim of this project is making a function that **returns a line**
ending with a newline, read from a file descriptor.

### Function Prototype
```c
int	get_next_line(int fd, char **line);
```

## Usage:

You can just call the fuction in your main in a loop, which will allow you to read the text
available on a file descriptor one line at a time until the EOF.

or:

Compile with the flag -D BUFFER_SIZE=xx. e.g:

`gcc main_stdin.c -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c && ./a.out`


BUFFER_SIZE=xx ill be used as the buffer size for the read calls in your get_next_line (if you don't emphasize it in compilation, the program will will use the default defined buffer size. 

main_stdin.c - is the file to read from.

### Return value
 | Value | Description         |
 |-----------|----------------------|
 |  1| A line has been read |
 |  0| EOF has been reached |
 |  -1| An error happened |


### Calling get_next_line from the main example:

```c
int main(int argc, char **argv)
{
	int fd, ret, line_count;
	char *line;

	line_count = 1;
	ret = 0;
	line = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf(" \n [ Return: %d ] | A line has been read #%d => %s\n", ret, line_count, line);
			line_count++;
			free(line);
		}
		printf(" \n [ Return: %d ] A line has been read #%d: %s\n", ret, line_count++, line);
		printf("\n");
		if (ret == -1)
			printf("-----------\n An error happened\n");
		else if (ret == 0)
		{
			printf("-----------\n EOF has been reached\n");
			free(line);
		}
		close(fd);
	}
```
  
This next line will return an integer that will be used as a parameter for the **get_next_line** function.
```c
fd = open(argv[1], O_RDONLY);
```
**get_next_line** function returns an **integer** that will be taken to evaluate all the lines until the file ends.





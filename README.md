# gnl

The aim of this project is making a function that returns a line
ending with a newline, read from a file descriptor.

Function Prototype
```int	get_next_line(int fd, char **line);```

Your program must compile with the flag -D BUFFER_SIZE=xx. which will be used as the buffer size for the read calls in your get_next_line.

gcc tests/main_stdin.c -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c

./a.out


Points to understand in GNL
According to our GNL subject Calling your function get_next_line in a loop will then allow you to read the text available on a file descriptor one line at a time until the EOF

Call GNL from the main

`int main(int argc, char **argv)
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
	}`
  
  
  This next line will return an integer that will be used as a parameter for the get_next_line function.

fd = open(argv[1], O_RDONLY);
get_next_line function will return an integer that will be taken to evaluate all the lines until the file ends.

Return value
Value	Description
1	A line has been read
0	EOF has been reached
-1	An error happened



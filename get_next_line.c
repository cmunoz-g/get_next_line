#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *buffer;
	char		*line;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// Load or update the buffer from the file descriptor
    // You need to implement this part to handle buffer reading and reallocation

    // Extract the next line from the buffer
    // You need to implement this part to find and return the next line

    // Handle end of file and errors
    // Return NULL if an error occurs or end of file is reached with no more lines

	return (line);
}

int	main(void)
{
	int fd = open("file", O_RDONLY);
	char *line = get_next_line(fd);
	if (line)
		printf("%s", line);
	else
		printf("null\n");
	
	return (0);
}
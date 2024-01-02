#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *buffer;
	char		*line;
	size_t		size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	
	
		



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
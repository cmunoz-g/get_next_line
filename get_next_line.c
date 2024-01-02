#include "get_next_line.h"

char	 *ft_read(int fd, char *buffer, char *line)
{
	char	*temp;
	char	*line_rd;
	ssize_t	bytes_rd;

	if (*buffer)
		line = ft_strjoin(line, buffer);
	bytes_rd = 1;
	while (bytes_rd > 0)
	{
		bytes_rd = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_rd] = '\0';
		line_rd = ft_findnl(buffer); 
		if (line_rd)
		{
			temp = ft_strjoin(line, line_rd);
			if (temp != NULL) 
			{
   				free(line); 
   				line = temp;
			}
			free(line_rd);
			return (line);
		}
		else
		{
			temp = ft_strjoin(line, buffer);
			if (temp != NULL) 
			{
   				free(line); 
   				line = temp;
			}
		}
	}
	if (bytes_rd < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char *buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)ft_calloc((BUFFER_SIZE + 1), 1);
		if (!buffer)
			return (NULL);
	}
	line = (char *)malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	line = ft_read(fd, buffer, line);
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
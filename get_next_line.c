#include "get_next_line.h"

void	ft_getbuff(char *buffer, char *line)
{
	char	*temp;
	char	*rest;

	temp = ft_findnl(buffer);
	if (!temp)
	{
		ft_strlcpy(line, buffer, BUFFER_SIZE);
		rest = buffer + BUFFER_SIZE;
		ft_strlcpy(buffer, rest, BUFFER_SIZE);
	}
	else
	{
		line = ft_strjoin(line, temp);
		rest = buffer + ft_strlen(temp);
		ft_strlcpy(buffer, rest, BUFFER_SIZE);
	}
}

char	 *ft_read(int fd, char *buffer, char *line)
{
	char	*temp;
	char	*rest;
	char	*line_rd;
	ssize_t	bytes_rd;

	if (*buffer)
		ft_getbuff(buffer, line); 
	bytes_rd = 1;
	while (bytes_rd > 0)
	{
		bytes_rd = read(fd, buffer, BUFFER_SIZE);
		if (bytes_rd < 0) 
		{
    		free(line);
    		return (NULL);
		}
		buffer[bytes_rd] = '\0';
		line_rd = ft_findnl(buffer);  //estaria bien gestionar el error de malloc en findnl de otra forma
		if (line_rd)
		{
			temp = ft_strjoin(line, line_rd);
			if (temp != NULL) 
			{
   				free(line); 
   				line = temp;
			}
			rest = buffer + ft_strlen(line_rd);
			free(line_rd);
    		ft_strlcpy(buffer, rest, BUFFER_SIZE);
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
	char *line;
	int i = 0;

	while (i != 3)
	{
 		line = get_next_line(fd);
		i++;
		printf("%s", line);
	}
	if (!line)
		printf("null\n");	
	return (0);
}
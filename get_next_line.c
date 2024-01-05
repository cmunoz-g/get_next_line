#include "get_next_line.h"

char	*ft_buffer(char *long_line, size_t len)
{
	char	*buffer;
	size_t	ll_size;
	size_t	i;
	
	i = 0;
	ll_size = ft_strlen(long_line);
	buffer = (char *)malloc((ll_size - len) + 1);
	if (!buffer)
	{
		free(long_line);
		return (NULL);
	}
	while ((i + len) < ll_size)
	{
		buffer[i] = long_line[i + len + 1];
		i++;
	}
	buffer[i] = '\0';\
	free(long_line);
	return (buffer);
}

char	*ft_linefill(char *long_line, size_t *len)
{
	size_t	i;
	char	*line;

	i = 0;
	*len = ft_findnl(long_line);
	line = (char *)malloc((*len) + 2);
	if (!line)
	{
		free(long_line);
		return (NULL);
	}
	while (long_line[i] && long_line[i] != '\n')
	{
		line[i] = long_line[i];
		i++;
	}
	if (long_line[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *long_line)
{
	char	*buffer;
	ssize_t	bytes_rd;

	buffer = (char *)malloc(BUFFER_SIZE + 1); 
	if (!buffer)
		return (NULL);
	while (!ft_strchr(long_line, '\n'))
	{
		bytes_rd = read(fd, buffer, BUFFER_SIZE);\
		if (bytes_rd == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_rd] = '\0';
		if (bytes_rd == 0)
		{
			free(buffer);
			return (long_line);
		}
		if (!long_line)
			long_line = ft_strdup(buffer);
		else
			long_line = ft_strjoin(long_line, buffer);       
	}
	free(buffer);
	return (long_line);
}

char	*get_next_line(int fd)
{
	static char *long_line = NULL;
	char		*line;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	long_line = ft_read(fd, long_line); //ft para guardar datos del archivo hasta que haya un salto de linea o se llegue a 0 en read
	if (!long_line)
		return (NULL);
	line = ft_linefill(long_line, &len); //ft para rellenar la linea
	if (!*long_line)
	{
		free(line);
		return (NULL);
	}
	else
	{
		long_line = ft_buffer(long_line, len); //ft para que el resto del buffer comience tras el salto de linea
		return (line);
	}
}

/*void	leaks(void)
{
	system("leaks a.out");
}*/

/*int	main(void)
{
	int fd = open("file", O_RDONLY);
	char *line;

	//atexit(leaks);
 	line = get_next_line(fd);
	while (line)
	{
		printf("line: %s", line);	
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
	return (0);
}*/
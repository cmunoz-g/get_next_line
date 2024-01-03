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
		return (NULL);
	while ((i + len) < ll_size)
	{
		buffer[i] = long_line[i + len];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

void	ft_linefill(char *long_line, char **line, ssize_t *len)
{
	size_t	i;

	i = 0;
	*len = ft_findnl(long_line);
	*line = (char *)malloc(*len + 1);
	if (!*line)
		return ;
	while (long_line[i] && long_line[i] != '\n')
	{
		*line[i] = long_line[i];
		i++;
	}
	if (long_line[i] == '\n')
		*line[i++] = '\n';
	*line[i] = '\0';
}

char	*ft_read(int fd, char *long_line)
{
	char	*buffer;
	ssize_t	bytes_rd;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(long_line, 10))
	{
		bytes_rd = read(fd, buffer, BUFFER_SIZE);
		if (bytes_rd == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_rd] = '\0';
		else if (bytes_rd = 0)
		{
			free(buffer);
			return (long_line);
		}
		else
			ft_strjoin(long_line, buffer);
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
	long_line = ft_read(fd, long_line); //funcion para guardar informacion en la str hasta que haya un salto de linea o se llegue a 0 en read.
	if (!long_line)
		return (NULL);
	ft_linefill(long_line, &line, &len); //ft para rellenar la linea
	if (!line)
		return (NULL);
	long_line = ft_buffer(long_line, len); //ft para dejar el buffer bien (moverlo hasta despues del salto de linea)
	if (!long_line)
		return (NULL);
	return (line);
}

int	main(void)
{
	int fd = open("file", O_RDONLY);
	char *line;

 	line = get_next_line(fd);
	printf("%s", line);	
	free(line);
	return (0);
}

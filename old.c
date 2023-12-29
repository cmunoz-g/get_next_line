#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*result;
	ssize_t	bytes;
	ssize_t	characters;

	bytes = read(fd, buffer, BUFFER_SIZE);
	characters = 0;
	if (bytes == -1)
		return (NULL);
	else if (bytes > 0 && bytes < BUFFER_SIZE)
	{
		result = (char *)malloc(bytes + 1);
		if (!result)
			return (NULL);
		ft_strcpy(result, buffer, (bytes + 1));
	}
	else if (bytes == 0)
	{
		result = (char *)malloc(1);
		if (!result)
			return (NULL);
		result[0] = '\0';
	}
	characters = ft_findchars(fd, buffer, bytes);
	if (characters < 0)
		return (NULL);
	result = (char *)malloc(characters + 1);
	if (!result)
		return (NULL);
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		ft_strcpy(result, buffer, (characters + 1));
		result += bytes;
	}
	return (result);
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

#include "get_next_line.h"

void  ft_strcpy(char *dest, const char *src, size_t size)
{
    size_t  i;

    i = 0;
    if (size > 0)
    {
        while (src[i] && i < (size))
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
}

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

size_t	ft_findnl(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

ssize_t ft_findchars(int fd, char *buffer, ssize_t bytes)
{
	size_t characters;

	characters = 0;
	while (bytes != 0)
	{
		characters += ft_findnl(buffer);
		if (ft_findnl(buffer) != BUFFER_SIZE)
			return (characters);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (-1);
	}
	return (characters);
}
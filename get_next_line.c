/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:07:01 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/01/09 14:12:04 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_buffer(char **long_line, size_t len)
{
	size_t	i;

	i = 0;
	while (i <= len && (**long_line))
	{
		(*long_line)++;
		i++;
	}
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

char	*ft_read(int fd, char *long_line, char *buffer)
{
	ssize_t	bytes_rd;

	while (!ft_strchr(long_line, '\n'))
	{
		bytes_rd = read(fd, buffer, BUFFER_SIZE);
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
	static char	*long_line = NULL;
	char		*line;
	char		*buffer;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	long_line = ft_read(fd, long_line, buffer);
	if (!long_line)
		return (NULL);
	line = ft_linefill(long_line, &len);
	if (!(*long_line))
	{
		free(line);
		return (NULL);
	}
	else
	{
		ft_buffer(&long_line, len);
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
	//printf("\n");
	return (0);
}*/
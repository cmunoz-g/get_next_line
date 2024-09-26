/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:38 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/09/26 14:27:02 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * Enhanced version of get_next_line that handles multiple file descriptors.
 * Uses an array to store the remaining lines for each file descriptor up to a
 * defined limit (U_LIMIT).
 * This allows simultaneous reading from different files without interference.
 */

void	auxfill(size_t len, size_t llsize, char *buff, char *long_line)
{
	size_t	i;

	i = 0;
	while (len < llsize && long_line[len])
	{
		buff[i] = long_line[len];
		i++;
		len++;
	}
	buff[i] = '\0';
}

char	*restline(char *long_line, char *line)
{
	char	*buff;
	size_t	llsize;
	size_t	len;

	if (!long_line)
		return (NULL);
	len = ft_strlen(line);
	if (!long_line[len])
	{
		free(long_line);
		return (NULL);
	}
	llsize = ft_strlen(long_line);
	buff = (char *)malloc((llsize - len) + 1);
	if (!buff)
		return (NULL);
	auxfill(len, llsize, buff, long_line);
	free(long_line);
	return (buff);
}

char	*ft_linefill(char *long_line)
{
	size_t	i;
	char	*line;

	if (!long_line)
		return (NULL);
	i = 0;
	line = (char *)malloc(ft_strlen(long_line) + 1);
	if (!line)
		return (NULL);
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
			free(long_line);
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
	static char	*long_line[U_LIMIT];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	long_line[fd] = ft_read(fd, long_line[fd], buffer);
	line = ft_linefill(long_line[fd]);
	long_line[fd] = restline(long_line[fd], line);
	return (line);
}
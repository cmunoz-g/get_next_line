/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:38 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/01/09 19:54:11 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*restline(char *long_line, size_t len)
{
	char 	*buff;
	size_t	llsize;
	size_t	i;
	
	i = 0;
	if (!long_line)
		return (NULL);
	if (!long_line[len])
	{
		free(long_line);
		return (NULL);
	}
	llsize = ft_strlen(long_line);
	buff = (char *)malloc((llsize - len) + 1);
	if (!buff)
		return (NULL);
	while ((i + len) < llsize)
	{
		buff[i] = long_line[i + len + 1];
		i++;
	}
	buff[i] = '\0';\
	free(long_line);
	return (buff);
}


char	*ft_linefill(char *long_line, size_t *len)
{
	size_t	i;
	char	*line;

	if (!long_line)
		return (NULL);
	i = 0;
	*len = ft_findnl(long_line);
	line = (char *)malloc((*len) + 1);
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
	long_line = ft_read(fd, long_line);
	//printf("ll:\n%s\n-------------\n",long_line);
	line = ft_linefill(long_line, &len);
	long_line = restline(long_line, len);
	return (line);
}

// void	leaks(void)
// {
// 	system("leaks a.out");
// }

// int	main(void)
// {
// 	int fd = open("file", O_RDONLY);
// 	char *line;
// 	int i =1;

// 	//atexit(leaks);
//  	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%d line: %s", i, line);	
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	free(line);
// 	close(fd);
// 	return (0);
// }
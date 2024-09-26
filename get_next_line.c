/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:38 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/09/26 14:24:45 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * auxfill
 *
 * Copies characters from the `long_line` to the `buff` buffer starting from
 * the position `len` up to `llsize` or until the end of `long_line` is reached.
 * The function ensures that `buff` is null-terminated at the end.
 *
 * @param len       Starting position in `long_line`.
 * @param llsize    Length of the `long_line`.
 * @param buff      Buffer to store the copied characters.
 * @param long_line Source string from which characters are copied.
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

/**
 * restline
 *
 * Returns a new string containing the remaining part of `long_line` after
 * the characters in `line`. Frees the original `long_line`.
 *
 * @param long_line Original string to be processed.
 * @param line      Processed part of `long_line` to be removed.
 * @return          Pointer to the remaining string or NULL if there are no remaining characters.
 */

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

/**
 * ft_linefill
 *
 * Extracts and returns a line (up to and including a newline character)
 * from the beginning of `long_line`. Allocates memory for the new line
 * and terminates it with a null character.
 *
 * @param long_line Input string to extract the line from.
 * @return          Pointer to the newly created line or NULL on error.
 */

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

/**
 * ft_read
 *
 * Reads from the file descriptor `fd` into `buffer` until a newline is found
 * or the end of the file is reached. Appends each read to `long_line`.
 * If an error occurs during reading, it frees allocated memory and returns NULL.
 *
 * @param fd        File descriptor to read from.
 * @param long_line Existing content to append new data.
 * @param buffer    Buffer to store read data temporarily.
 * @return          Pointer to the updated `long_line` or NULL on error.
 */

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

/**
 * get_next_line
 *
 * Reads the next line from the file descriptor `fd`. Uses a static variable
 * `long_line` to store the remainder of the previous read. Allocates a buffer
 * for reading from the file. Calls helper functions to fill and update
 * `long_line` and `line`.
 *
 * @param fd    File descriptor to read from.
 * @return      The next line read or NULL on error or when no more lines are available.
 */

char	*get_next_line(int fd)
{
	static char	*long_line = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	long_line = ft_read(fd, long_line, buffer);
	line = ft_linefill(long_line);
	long_line = restline(long_line, line);
	return (line);
}
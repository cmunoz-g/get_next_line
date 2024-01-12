/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:12:41 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/01/12 13:04:43 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	size_t	destlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	j = destlen;
	i = 0;
	if (destsize <= destlen)
		return (srclen + destsize);
	else
	{
		while (src[i] && j < (destsize - 1))
			dest[j++] = src[i++];
		dest[j] = '\0';
		return (srclen + destlen);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s3size;
	size_t	i;
	size_t	size;

	s3size = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = (char *)malloc(s3size);
	if (s3 == NULL)
		return (NULL);
	size = ft_strlen(s1);
	i = 0;
	if (size > 0)
	{
		while (s1[i] && i < size)
		{
			s3[i] = s1[i];
			i++;
		}
		s3[i] = '\0';
	}
	ft_strlcat(s3, s2, s3size);
	free((void *)s1);
	return (s3);
}

char	*ft_strchr(const char *str, int c)
{
	char	ch;

	ch = (char)c;
	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*cpy;
	size_t	i;

	size = ft_strlen(s) + 1;
	cpy = (char *)malloc(size);
	if (!cpy)
		return (NULL);
	i = 0;
	if (size > 0)
	{
		while (s[i] && i < size)
		{
			cpy[i] = s[i];
			i++;
		}
		cpy[i] = '\0';
	}
	return (cpy);
}

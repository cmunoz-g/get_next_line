#include "get_next_line.h"

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

size_t  ft_strlcat(char *dest, const char *src, size_t destsize)
{
    size_t  i;
    size_t  j;
    size_t  destlen;
    size_t  srclen;

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

size_t  ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t  i;

    i = 0;
    if (size > 0)
    {
        while (src[i] && i < size)
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s3size;

	s3size = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = (char *)malloc(s3size);
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, s1, ft_strlen(s1));
	ft_strlcat(s3, s2, s3size);
    free((void *)s1);
	return (s3);	
}

size_t  ft_findnl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
    return (i);
}

char    *ft_strchr(const char *str, int c)
{
    char    ch;

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

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*cpy;

	size = ft_strlen(s) + 1;
	cpy = (char *)malloc(size);
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, s, size);
	return (cpy);
}
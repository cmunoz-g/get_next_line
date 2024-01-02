#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	totalsize;

	totalsize = nmemb * size;
	if (nmemb != 0 && totalsize / nmemb != size)
		return (NULL);
	res = malloc(totalsize);
	if (res == NULL)
		return (NULL);
	ft_memset(res, 0, totalsize);
	return (res);
}

void    *ft_memset(void *str, int c, size_t n)
{
    unsigned char *cpy;

    cpy = str;
    while (n > 0)
    {
        *cpy = (unsigned char)c;
        cpy++;
        n--;
    }
    return (str);
}

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
	return (s3);	
}

char    *ft_findnl(char *str)
{
	char	*new_line;
	size_t	i;

	i = 0;
	while (*str && *str != '\n')
	{
		i++;
		str++;	
	}
	if (!(*str))
		return (NULL);
	else
	{
		new_line = (char *)malloc(i + 1);
		if (!new_line)
			return (NULL);
		ft_strlcpy(new_line, str, (i + 1));
	}
	return (new_line);
}
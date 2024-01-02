#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

void	*ft_calloc(size_t nmemb, size_t size);
char    *ft_findnl(char *str);
void    *ft_memset(void *str, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlcat(char *dest, const char *src, size_t destsize);
size_t  ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);

#endif //GET_NEXT_LINE_H
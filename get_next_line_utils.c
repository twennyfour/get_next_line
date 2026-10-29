#include "get_next_line.h"
#include <stdlib.h>

size_t  ft_strlen(const char *str)
{
    const char  *start;

    start = str;
    while (*str)
        str++;
    return (str - start);
}

char    *ft_strchr(const char *s, int c)
{
    while (*s && *s != (char)c)
        s++;
    if (!*s && (char)c)
        return (NULL);
    return ((char *)s);
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char       *d;
    const unsigned char *s;

    d = dest;
    s = src;
    while (n--)
        *d++ = *s++;
    return (dest);
}

char    *ft_substr(char const *s, size_t len)
{
    char    *res;

    res = malloc(len + 1);
    if (!res)
        return (NULL);
    ft_memcpy(res, s, len);
    res[len] = '\0';
    return (res);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  ls1;
    size_t  ls2;
    char    *res;

    ls1 = ft_strlen(s1);
    ls2 = ft_strlen(s2);
    res = malloc(sizeof(char) * (ls1 + ls2 + 1));
    if (!res)
        return (NULL);
    ft_memcpy(res, s1, ls1);
    ft_memcpy(res + ls1, s2, ls2 + 1);
    return (res);
}

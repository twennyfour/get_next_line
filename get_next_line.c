#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char *read_and_store(int fd, char *buffer, char *accumulated)
{
    char    *tmp;
    ssize_t bytes_read;

    bytes_read = 1;
    while (!ft_strchr(buffer, '\n') && bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(accumulated);
            buffer[0] = '\0';
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        tmp = accumulated;
        accumulated = ft_strjoin(accumulated, buffer);
        free(tmp);
        if (!accumulated)
            return (NULL);
    }
    return (accumulated);
}

static char *extract_line(char *accumulated)
{
    char    *start;
    char    *end;

    start = accumulated;
    end = ft_strchr(accumulated, '\n');
    if (end)
        return (ft_substr(start, end - start + 1));
    return (ft_strjoin(start, ""));
}

static void update_buffer(char *buffer, char *accumulated)
{
    char    *end;

    end = ft_strchr(accumulated, '\n');
    if (!end)
        return ;
    ft_memcpy(buffer, end + 1, ft_strlen(end));
}

char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    char        *line;
    char        *accumulated;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 1000000)
        return (NULL);
    accumulated = ft_substr(buffer, ft_strlen(buffer));
    if (!accumulated)
        return (NULL);
    accumulated = read_and_store(fd, buffer, accumulated);
    if (!accumulated || !*accumulated)
        return (free(accumulated), NULL);
    line = extract_line(accumulated);
    update_buffer(buffer, accumulated);
    free(accumulated);
    return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
*/

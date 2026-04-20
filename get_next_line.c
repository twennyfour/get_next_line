/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:53:19 by mleitao           #+#    #+#             */
/*   Updated: 2026/04/20 17:09:58 by mleitao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char	*read_and_store(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (bytes_read < 0)
			return (free(stash), NULL);
		buffer[bytes_read] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*start;

	if (!*stash)
		return (NULL);
	start = stash;
	stash = ft_strchr(stash, '\n');
	return (ft_substr(start, stash - start));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		buf[BUFFER_SIZE];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 1000000)
		return (NULL);
	stash = read_and_store(fd, stash);
	line = extract_line(stash);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("get_next_line.c", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

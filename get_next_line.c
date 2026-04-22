/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:53:19 by mleitao           #+#    #+#             */
/*   Updated: 2026/04/22 13:49:18 by mleitao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*read_and_store(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	bytes_read;

	if (!stash)
		stash = ft_strjoin("", "");
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
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
	char	*end;

	if (!stash || !*stash)
		return (NULL);
	start = stash;
	end = ft_strchr(stash, '\n');
	if (end)
		return (ft_substr(start, end - start + 1));
	return (ft_strjoin(start, ""));
}

char	*update_stash(char *stash)
{
	char	*end;

	if (!stash)
		return (NULL);
	end = ft_strchr(stash, '\n');
	if (!end)
		return (free(stash), NULL);
	return (ft_memcpy(stash, end + 1, ft_strlen(end)));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 1000000)
		return (NULL);
	stash = read_and_store(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("v.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/

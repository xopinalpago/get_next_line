/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:14:19 by rmeriau           #+#    #+#             */
/*   Updated: 2023/05/16 12:03:06 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*lib(char *to_free, char *buf)
{
	char	*temp;

	temp = ft_strjoin(to_free, buf);
	free(to_free);
	return (temp);
}

char	*get_line(char *data)
{
	char	*line;
	int		i;

	i = 0;
	if (!data[i])
		return (NULL);
	while (data[i] && data[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (data[i] && data[i] != '\n')
	{
		line[i] = data[i];
		i++;
	}
	if (data[i] == '\n')
		line[i] = '\n';
	i++;
	line[i] = '\0';
	return (line);
}

char	*new_line(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old[i] != '\0' && old[i] != '\n')
		i++;
	if (!old[i])
	{
		free(old);
		return (NULL);
	}
	new = ft_calloc(ft_strlen(old) - i + 1, sizeof(char));
	i++;
	while (old[i] != '\0')
	{
		new[j] = old[i];
		i++;
		j++;
	}
	free(old);
	return (new);
}

char	*get_read(char *temp, int fd)
{
	char	*buf;
	int		size;

	if (!temp)
		temp = ft_calloc(1, sizeof(char));
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	size = 1;
	while (size > 0)
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
		{
			free(buf);
			free(temp);
			return (NULL);
		}
		buf[size] = 0;
		temp = lib(temp, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	res = get_read(res, fd);
	if (!res)
		return (NULL);
	line = get_line(res);
	res = new_line(res);
	return (line);
}

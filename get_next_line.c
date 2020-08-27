/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 18:35:08 by dbliss            #+#    #+#             */
/*   Updated: 2020/06/16 17:27:20 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strjoin(char *s1, char *s2)
{
	char *s3;

	s3 = 0;
	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	else if (s1 && s2)
	{
		if (!(s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
			return (0);
		ft_strcpy(s3, s1);
		free(s1);
		ft_strcat(s3, s2);
	}
	return (s3);
}

int			output(char **line_left, char **line, int last_read)
{
	int		n;
	char	*tmp;

	if (last_read < 0)
		return (-1);
	if (*line_left && (n = ft_strchrn(*line_left, '\n')) >= 0)
	{
		(*line_left)[n] = '\0';
		*line = ft_strdup(*line_left);
		tmp = ft_strdup(*line_left + n + 1);
		free(*line_left);
		*line_left = tmp;
		return (1);
	}
	else if (*line_left)
	{
		*line = *line_left;
		*line_left = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		*line_left[MAX_FD];
	char			buf[BUFFER_SIZE + 1];
	int				last_read;
	int				n;
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (-1);
	while ((last_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[last_read] = '\0';
		line_left[fd] = ft_strjoin(line_left[fd], buf);
		if ((n = ft_strchrn(line_left[fd], '\n')) >= 0)
		{
			(line_left[fd])[n] = '\0';
			*line = ft_strdup(line_left[fd]);
			tmp = ft_strdup(line_left[fd] + n + 1);
			free(line_left[fd]);
			line_left[fd] = tmp;
			return (1);
		}
	}
	return (output(&line_left[fd], line, last_read));
}

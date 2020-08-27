/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 18:35:08 by dbliss            #+#    #+#             */
/*   Updated: 2020/06/03 18:35:10 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strjoin(char *s1, char *s2)
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
		free(s1); // это остаток, но его в принципе можно освободить в др месте, подумать!!!
		ft_strcat(s3, s2);
	}
	return (s3);
}

int	split_line(char **tmp_line, char **line, int n)
{
	char *tmp;
	int len;

	(*tmp_line)[n] = '\0';
	*line = ft_strdup(*tmp_line);
	len = ft_strlen(*tmp_line + n + 1);
	tmp = ft_strdup(*tmp_line + n + 1);
	free(*tmp_line);
	*tmp_line = tmp;
	return (1);

}

int		ret(char **tmp_line, char **line, int fd)
{
	int n;

	if (fd < 0)
		return (-1);
	if (*tmp_line && (n = ft_strchrr(*tmp_line, '\n')) >= 0)
		return (split_line(tmp_line, line, n));
	else if (*tmp_line)
	{
		*line = *tmp_line;
		*tmp_line = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);

}

int					get_next_line(int fd, char **line)
{
	static char		*tmp_line[MAX_FD];
	char			buf[BUFFER_SIZE + 1];
	int				read_size;
	int				cut_idx;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		tmp_line[fd] = ft_strjoin(tmp_line[fd], buf);
		if ((cut_idx = ft_strchr(tmp_line[fd], '\n')) >= 0)
			return (split_line(&tmp_line[fd], line, cut_idx));
	}
	return (ret(&tmp_line[fd], line, read_size));
}

#include <stdio.h>
#include <fcntl.h>

int   main(int ac, char **av)
{
  char  *line;
  int   fd1;
  int   fd2;
  int	fd3;

  fd1 = open(av[1], O_RDONLY);
  fd2 = open(av[2], O_RDONLY);
  fd3 = open(av[3], O_RDONLY);
  printf("%d\n", get_next_line(fd1, &line));
  return (0);
}
/*int main(void)
{
    char    *line;
    int     fd;

    fd = open("text.txt", O_RDONLY);
	get_next_line(fd, &line);    
	printf("%s\n", line);
	get_next_line(fd, &line);    
	printf("%s\n", line);
	get_next_line(fd, &line);    
	printf("%s\n", line);
	
}
*/
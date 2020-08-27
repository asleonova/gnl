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

char			*ft_strjoin(char const *s1, char const *s2)
{
	char *s3;

	s3 = 0;
	if (s1 && s2)
	{
		if (!(s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
			return (NULL);
		ft_strcpy(s3, s1);
		ft_strcat(s3, s2);
	}
	return (s3);
}


char	*verify_tmp_line(char *tmp_line, char **line)
{
	char *n;

	n = NULL;
	if (tmp_line) 
	{
		if ((n = ft_strchr(tmp_line, '\n')))
		{
			*n = '\0'; 
			*line = ft_strdup(tmp_line); 
			ft_strcpy(tmp_line, ++n);
		}
		else
		{
			*line = ft_strdup(tmp_line); 
			while (*tmp_line)
			*tmp_line++ = '\0';
		}
	}
	else
	{
		if(!(*line = (char *)(malloc)(sizeof(char))))
			return (NULL);
		*line[0] = '\0';
	}
	return (n);
}

int gnl(int fd, char **line, char **tmp_line)
{
    char buf[BUFFER_SIZE + 1]; 
	int last_read;
	char *n;
	char *leaks;

	n = verify_tmp_line(*tmp_line, line);
	while (!n && (last_read = read(fd, buf, BUFFER_SIZE))) 
	{
		buf[last_read] = '\0';
		if ((n = ft_strchr(buf, '\n')))
		{
			*n = '\0';
			n++;
			*tmp_line = ft_strdup(n);
		}
		leaks = *line; 
		if (!(*line = ft_strjoin(*line, buf)) || last_read < 0)
			return (-1);
		free(leaks);
	}
	return ((last_read || ft_strlen(*line)) || ft_strlen(*tmp_line) ? 1 : 0);
}

int					get_next_line(int  fd, char **line)
{
	static char		*files[MAX_FD];
	int				ret;

	if (!line || (fd < 0 || fd >= MAX_FD))
		return (-1);

	ret = gnl(fd, line, &files[fd]);
	return (ret);
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
  /* printf("%s\n", line);
  get_next_line(fd2, &line);
  printf("%s\n", line);
  get_next_line(fd3, &line);
  printf("%s\n", line);
  get_next_line(fd1, &line);
  printf("%s\n", line);
  get_next_line(fd1, &line);
  printf("%s\n", line);
  get_next_line(fd3, &line);
  printf("%s\n", line);
  get_next_line(fd3, &line);
  printf("%s\n", line);
  get_next_line(fd3, &line);
  printf("%s\n", line);
  get_next_line(fd3, &line);
  printf("%s", line);
  */
  return (0);
}
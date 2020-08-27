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

int 	output(char **line_left, char **line, int last_read) // фун-я вызывается тогда, когда у нас файл дочитался до конца
{
	int n;
    char *tmp;

    if (last_read < 0) // это значит, что при чтении произошла ошибка, и read вернул отрицательное значение
        return (-1);
	if (*line_left && (n = ft_strchrn(*line_left, '\n')) >= 0) // если в прочитанном остатке и конец файла, и новая линия
    {
        (*line_left)[n] = '\0';
	    *line = ft_strdup(*line_left);
	    tmp = ft_strdup(*line_left + n + 1);
	    free(*line_left);
	    *line_left = tmp;
        return (1);
    }
    else if (*line_left) // условие для последней строки
	{
		*line = *line_left;
		*line_left = 0;
		return (0);
	}
	*line = ft_strdup(""); // когда нечего было читать
	return (0);
}

int					get_next_line(int  fd, char **line)
{
    static char		*line_left[MAX_FD];
	char            buf[BUFFER_SIZE + 1];
	int				last_read;
    int             n;
    char            *tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd >= MAX_FD) // это все ошибки
		return (-1);
	while ((last_read = read(fd, buf, BUFFER_SIZE)) > 0) // если у нас что-то прочиталось, то есть если фун-я read вернула положительное значение
	{
		buf[last_read] = '\0'; // ставим знак конца строки на том моменте, на котором дочиталось (read возвращается кол-во прочитанных символов)
		line_left[fd] = ft_strjoin(line_left[fd], buf); // запишем в line_left все то, что в буфере, а также то, что было в остатке с прошлого вызова (на первом "заходе" запишет туда только то, что в буфер)
		if ((n = ft_strchrn(line_left[fd], '\n')) >= 0) // если в прочитанном куске текста встретилась новая линия, то запомнить этот индекс
        {
            (line_left[fd])[n] = '\0'; // поставить конец строки там, где встретилась новая линия
	        *line = ft_strdup(line_left[fd]); // записать в line (в heap) то, что было в left_line
	        tmp = ft_strdup(line_left[fd] + n + 1); // так мы запишем наш остаток в tmp
	        free(line_left[fd]); // освобождаем все, что было в line_left (так как мы уже записали нужное нам в line
            line_left[fd] = tmp; // возвращаем остаток в line_left
            return (1);
        }
           
	}
	return (output(&line_left[fd], line, last_read));
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
  printf("%s\n", line);
  /* get_next_line(fd1, &line);
  printf("%s\n", line);
  get_next_line(fd1, &line);
  printf("%s\n", line);
  get_next_line(fd1, &line);
  printf("%s\n", line);
  get_next_line(fd1, &line);
  printf("%s\n", line);
  get_next_line(fd1, &line);
  printf("%s\n", line);
  get_next_line(fd1, &line);
  printf("%s\n", line);
  */
 // get_next_line(fd1, &line);
//  printf("%s\n", line);
 // get_next_line(fd1, &line);
//  printf("%s", line);
  
  return (0);
}
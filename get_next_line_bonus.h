/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:48:28 by dbliss            #+#    #+#             */
/*   Updated: 2020/06/16 17:48:35 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char			*ft_strcat(char *dest, const char *src);
size_t			ft_strlen(const char *str);
int				ft_strchrn(char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *src);
char			*ft_strjoin(char *s1, char *s2);
int				output(char **line_left, char **line, int last_read);
int				get_next_line(int fd, char **line);

# ifndef MAX_FD
#  define MAX_FD 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#endif

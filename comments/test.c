/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 23:51:37 by dbliss            #+#    #+#             */
/*   Updated: 2020/06/08 23:52:25 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (!(*line = (char *)(malloc)(sizeof(char))))
			return (0);
		*line[0] = '\0';
	}
	return (n);
}

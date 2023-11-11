/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:13:15 by rouarrak          #+#    #+#             */
/*   Updated: 2022/11/02 23:14:53 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*negga_tive(char **saved, char **l, char *buf)
{
	free(buf);
	*l = *saved;
	*saved = NULL;
	if (*l && **l == '\0')
	{
		free(*l);
		return (NULL);
	}
	return (*l);
}

static void	getsub(char **saved, char **l)
{
	char	*tmp;
	char	*sub;
	int		len;

	sub = ft_strchr(*saved, '\n');
	len = ft_strlen(sub);
	*l = ft_substr (*saved, 0, sub - *saved + 1);
	tmp = *saved;
	*saved = ft_substr(sub + 1, 0, len);
	free(tmp);
}

char	*get_next_line(int fd)
{
	char		*l;
	static char	*saved[OPEN_MAX];
	char		*buf;
	ssize_t		readbytes;

	l = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	while (fd >= 0 && !ft_strchr(saved[fd], '\n'))
	{
		readbytes = read(fd, buf, BUFFER_SIZE);
		if (readbytes > 0)
		{
			buf[readbytes] = 0;
			saved[fd] = ft_strjoin(saved[fd], buf);
		}
		if (readbytes <= 0)
			return (negga_tive(&saved[fd], &l, buf));
	}
	free (buf);
	if (fd >= 0 && saved[fd] && ft_strchr(saved[fd], '\n'))
	{
		getsub(&saved[fd], &l);
	}
	return (l);
}

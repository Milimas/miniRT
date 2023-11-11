/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:13:15 by rouarrak          #+#    #+#             */
/*   Updated: 2022/11/03 00:12:14 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*negga_tif(char **saved, char **l, char *buf)
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
	free (tmp);
}

char	*get_next_line(int fd)
{
	char		*l;
	static char	*saved;
	char		*buf;
	ssize_t		readbytes;

	l = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	while (fd >= 0 && !ft_strchr(saved, '\n'))
	{
		readbytes = read(fd, buf, BUFFER_SIZE);
		if (readbytes > 0)
		{
			buf[readbytes] = '\0';
			saved = ft_strjoin(saved, buf);
		}
		else
			return (negga_tif(&saved, &l, buf));
	}
	free (buf);
	if (fd >= 0 && saved && ft_strchr(saved, '\n'))
	{
		getsub(&saved, &l);
	}
	return (l);
}

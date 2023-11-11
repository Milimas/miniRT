/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:26:29 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/09/10 19:45:54 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

int	n_lines(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", 2))
			i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

int	nospace_strlen(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			size++;
			i++;
		}
		else
		{
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i])
				size++;
		}
	}
	return (size);
}

static char	*fill_res(int i, char *res, char *str)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			res[j] = str[i];
			i++;
			j++;
		}
		else
		{
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i])
			{
				res[j] = ' ';
				j++;
			}
		}
	}
	res[j] = '\0';
	return (res);
}

char	*rm_space(char *str)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = nospace_strlen(str);
	i = 0;
	j = 0;
	res = malloc((len + 1) * sizeof(char));
	while (str[i] && str[i] == ' ')
		i++;
	res = fill_res(i, res, str);
	return (res);
}

char	**read_file(char *file)
{
	int		fd;
	int		i;
	int		nl;
	char	**file_tab;
	char	*hold;

	i = 0;
	fd = open(file, O_RDONLY, 0777);
	nl = n_lines(fd);
	if (nl == 0)
		return (NULL);
	close(fd);
	fd = open(file, O_RDONLY, 0777);
	file_tab = malloc((nl + 1) * sizeof(char *));
	while (i < nl)
	{
		hold = get_next_line(fd);
		if (ft_strncmp(hold, "\n", 2))
			file_tab[i++] = rm_space(hold);
		free(hold);
	}
	file_tab[i] = NULL;
	return (file_tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:52:13 by rouarrak          #+#    #+#             */
/*   Updated: 2023/11/28 09:29:48 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str1 == *str2 && *str1 && *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

void	free_split(char **split)
{
	char	**tmp;

	if (!split)
		return ;
	tmp = split;
	while (*split)
		free(*split++);
	free(tmp);
}

double static	str_to_double_2(const char *str, int flag, double fract)
{
	double	result;

	result = 0.0;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			if (flag)
			{
				result = result + (*str - '0') * fract;
				fract /= 10;
			}
			else
				result = result * 10 + (*str - '0');
		}
		else if (*str == '.')
			flag = 1;
		else
		{
			printf("Error\nAn parameter must be a number check it!\n");
			exit(0);
		}
		str++;
	}
	return (result);
}

double	str_to_double(const char *str)
{
	double	result;
	double	fract;
	int		flag;
	int		sign;

	result = 0.0;
	fract = 0.1;
	sign = 1;
	flag = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	result = str_to_double_2(str, flag, fract);
	return (result * sign);
}

int	param_num(char *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t')
			&& (str[i + 1] && str[i + 1] != '\n'))
			cpt++;
		i++;
	}
	return (cpt);
}

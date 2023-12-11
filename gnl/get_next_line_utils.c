/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:13:18 by rouarrak          #+#    #+#             */
/*   Updated: 2023/08/26 01:43:04 by rouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			i;
	size_t			j;
	char			*str;
	unsigned long	l1;
	unsigned long	l2;

	i = 0;
	j = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *) malloc(l1 + l2 + 1);
	if (!str)
		return (NULL);
	while (i < l1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j <= l2)
	{
		str[i + j] = s2[j];
		j++;
	}
	free((char *)s1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(s);
	while (i < size)
	{
		if (s[i] == (const char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t			i;
// 	char			*str;
// 	size_t			m;
// 	size_t			l;

// 	i = 0;
// 	m = 0;
// 	l = ft_strlen(s);
// 	if (!s)
// 		return (0);
// 	else if (l - start > len)
// 		m = len;
// 	else
// 		m = l - start;
// 	str = malloc(len + 1);
// 	if (!str)
// 		return (NULL);
// 	while (s[start + i] && i < len)
// 	{
// 		str[i] = s[start + i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

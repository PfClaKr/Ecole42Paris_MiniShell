/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:21:43 by ychun             #+#    #+#             */
/*   Updated: 2023/01/16 18:24:13 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

char	*ft_strcpy_gnl(char *dest, char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[ft_strlen_gnl(s1) + j] = '\0';
	return (dest);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new_s;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = 0;
	}
	if (!s1 || !s2)
	{
		free(s2);
		return (0);
	}
	new_s = (char *)malloc((sizeof(char) * (len_s1 + len_s2 + 1)));
	if (!new_s)
		return (0);
	new_s = ft_strcpy_gnl(new_s, s1, s2);
	free (s1);
	return (new_s);
}
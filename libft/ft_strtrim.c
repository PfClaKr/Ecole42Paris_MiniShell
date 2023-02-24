/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:34:03 by aboyer            #+#    #+#             */
/*   Updated: 2022/11/08 15:34:06 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_sep(char ch, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (ch == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ind_right(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && check_sep(s1[i], set))
		i++;
	return (i);
}

int	ind_left(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (i > 0 && check_sep(s1[i - 1], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	start = ind_right(s1, set);
	end = ind_left(s1, set);
	if (start > end)
	{
		str = malloc(sizeof(char));
		str[0] = 0;
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (!str)
		return (NULL);
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}

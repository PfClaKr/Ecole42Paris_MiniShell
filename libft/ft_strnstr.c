/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:43:57 by aboyer            #+#    #+#             */
/*   Updated: 2022/11/08 13:43:59 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	i2;
	size_t	little_len;

	i = 0;
	i2 = 0;
	little_len = 0;
	while (little[little_len])
		little_len++;
	if (little_len == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (little[i2] == big[i + i2] && i + i2 < len)
		{
			if (i2 == little_len - 1)
				return ((char *)big + i);
			i2++;
		}
		i2 = 0;
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:45:52 by aboyer            #+#    #+#             */
/*   Updated: 2022/11/07 16:45:53 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*str_src;
	char	*str_dest;

	i = 0;
	str_src = (char *)src;
	str_dest = (char *)dest;
	if (str_src < str_dest)
	{
		while (n-- > 0)
			str_dest[n] = str_src[n];
	}
	else
	{
		while (i < n)
		{
			str_dest[i] = str_src[i];
			i++;
		}
	}
	return (dest);
}

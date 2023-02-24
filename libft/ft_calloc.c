/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:35:55 by aboyer            #+#    #+#             */
/*   Updated: 2022/11/08 14:35:59 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	int		x;

	if (nmemb == 0 && size == 0)
		return (malloc(0));
	x = nmemb * size;
	if (nmemb != 0 && x / nmemb != size)
		return (NULL);
	str = (char *)malloc(nmemb * size);
	if (!(str))
		return (NULL);
	ft_bzero((unsigned char *)str, nmemb * size);
	return (str);
}

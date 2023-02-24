/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:50:45 by ychun             #+#    #+#             */
/*   Updated: 2023/02/23 16:52:41 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr_env(char const *s, unsigned int start, int len)
{
	size_t	i;
	int		j;
	char	*str;

	i = start;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (len <= 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (i < ft_strlen(s) && j < len)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = 0;
	return (str);
}

void	seperate_env_argv(char *argv, char **key, char **value)
{
	int	i;

	i = -1;
	while (argv[i] && argv[i] != '=')
	{
		if (argv[i] == '=')
			break ;
	}
	*key = ft_substr(argv, 0, i);
	if (ft_strlen(argv) - i)
	{
		*value = ft_substr(argv, i + 1, ft_strlen(argv) - i);
		if (!(*key) || !(*value))
			ft_error("Allocation failed", STDERR_FILENO);
	}
	else
		*value = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:41 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 03:17:28 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_check_flag(char **cmd, int *i, int *n)
{
	int	j;

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] == 'n')
	{
		while (cmd[*i] && cmd[*i][0] == '-' && cmd[*i][1] == 'n')
		{
			j = 1;
			while (cmd[*i][j])
			{
				if (cmd[*i][j] != 'n')
					return ;
				j++;
			}
			(*i)++;
		}
		*n = 1;
	}
}

int	echo(char **cmd)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (!cmd[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	echo_check_flag(cmd, &i, &n);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}

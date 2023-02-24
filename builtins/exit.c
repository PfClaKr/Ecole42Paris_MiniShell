/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:46 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 16:31:52 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long	ft_atoi_exit(const char *nptr)
{
	long long	result;
	int			neg;
	int			i;

	result = 0;
	neg = 1;
	i = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		neg = neg * -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * neg);
}

int	check_long_long(char *num)
{
	if (num[0] == '+' || num[0] == '-')
	{
		if (ft_strlen(num) > ft_strlen("+9223372036854775807"))
			return (0);
		if (num[0] == '+' && ft_strncmp(num, "+9223372036854775807", 20) > 0)
			return (0);
		if (num[0] == '-' && ft_strncmp(num, "-9223372036854775808", 20) > 0)
			return (0);
	}
	else
	{
		if (ft_strlen(num) > ft_strlen("9223372036854775807"))
			return (0);
		if (ft_strncmp(num, "9223372036854775807", 19) > 0)
			return (0);
	}
	return (1);
}

int	check_nb(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-' || num[0] == '+')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	if (check_long_long(num) == 0)
		return (0);
	return (1);
}

int	exit_cmd(char **cmd)
{
	long long	nb;

	printf("exit\n");
	if (!cmd[1])
		return (g_global.ret);
	if (check_nb(cmd[1]) == 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (-2);
	}
	nb = ft_atoi_exit(cmd[1]);
	if (nb < 0)
		return ((unsigned int)nb % 256);
	else if (nb > 255)
		return (nb % 256);
	else
		return (nb);
}

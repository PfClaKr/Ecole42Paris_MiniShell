/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_incmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:49:30 by ychun             #+#    #+#             */
/*   Updated: 2023/02/19 15:49:10 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_quote(char *cmd, int i, int type)
{
	if (type == T_SINGLE_QUOTES)
	{
		while (cmd[i] && cmd[i] != '\'')
		{
			if (cmd[i] == '\\' && cmd[i + 1] == '\'')
				i++;
			i++;
		}
	}
	else if (type == T_DOUBLE_QUOTES)
	{
		while (cmd[i] && cmd[i] != '\"')
		{
			if (cmd[i] == '\\' && cmd[i + 1] == '\"')
				i++;
			i++;
		}
	}
	if (!cmd[i])
		return (find_quote_return(type));
	return (i);
}

int	find_quote_end(char *cmd, int i)
{
	if (!cmd[i + 1])
		return (is_which_quote(cmd[i]));
	if (cmd[i] == '\'')
	{
		i = find_quote(cmd, i + 1, T_SINGLE_QUOTES);
		if (i < 0)
			return (i);
	}
	else if (cmd[i] == '\"')
	{
		i = find_quote(cmd, i + 1, T_DOUBLE_QUOTES);
		if (i < 0)
			return (i);
	}
	return (i);
}

int	check_quotes_incmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			i++;
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i = find_quote_end(cmd, i);
			if (i < 0)
				return (i);
			i++;
		}
		while (cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == '\'' || cmd[i] == '\"')
				break ;
			i++;
		}
	}
	return (i);
}

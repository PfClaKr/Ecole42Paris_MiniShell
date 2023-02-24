/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:50 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 17:11:40 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_env_argv(char *key)
{
	int	i;

	i = -1;
	if (!key)
		return (1);
	if (!ft_strcmp(key, "$?"))
		return (0);
	if (ft_isalpha(key[0]) || key[0] == '_' || ft_isdigit(key[0]))
	{
		if (ft_isdigit(key[0]))
			return (1);
	}
	while (key[++i])
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
			return (1);
	}
	return (0);
}

int	check_have_equal(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '=')
			return (1);
	return (0);
}

void	ft_free_row_env(char **env)
{
	int	j;

	j = -1;
	while (env && env[++j])
		free(env[j]);
	if (env)
		free(env);
}

char	**ft_split_env(char *cmd, int *flag)
{
	int		i;
	char	**rst;

	i = -1;
	rst = (char **)malloc(sizeof(char *) * 3);
	while (cmd[++i])
	{
		if (cmd[i] == '=')
		{
			*flag = 1;
			rst[0] = ft_substr_env(cmd, 0, i);
			if (!rst[0])
				rst[0] = ft_strdup("=");
			break ;
		}
	}
	if (*flag == 0)
	{
		rst[0] = ft_substr_env(cmd, 0, ft_strlen(cmd));
		rst[1] = NULL;
	}
	else
		rst[1] = ft_substr_env(cmd, i + 1, ft_strlen(cmd) - (i + 1));
	rst[2] = NULL;
	return (rst);
}

int	export(char **cmd, t_env_list *env_list)
{
	int		i;
	char	**row_env;
	int		flag;

	i = 0;
	if (cmd[1] == NULL)
		return (env(cmd, env_list, 1));
	while (cmd[++i])
	{
		flag = 0;
		row_env = ft_split_env(cmd[i], &flag);
		if (check_env_argv(row_env[0]))
			return (ft_putstr_fd("export: ", 2), ft_putstr_fd(row_env[0], 2),
				ft_putstr_fd(" : not a valid identifier\n", 2),
				ft_free_row_env(row_env), 1);
		if (flag == 1)
			set_new_env(env_list, row_env[0], row_env[1]);
		ft_free_row_env(row_env);
	}
	return (0);
}

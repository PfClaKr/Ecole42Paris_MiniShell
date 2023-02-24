/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:38 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 16:32:09 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char **cmd, char *value, t_env_list **env)
{
	char	buffer[4096];
	int		i;
	t_env	*env_value;

	i = chdir(value);
	if (i == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	env_value = find_env_by_key(*env, "PWD");
	getcwd(buffer, 4096);
	if (!env_value)
	{
		set_new_env(*env, "PWD", buffer);
		return (0);
	}
	update_env_value(env, "OLDPWD", env_value->value);
	update_env_value(env, "PWD", buffer);
	return (0);
}

int	cd1(t_env *env_value)
{
	if (!env_value)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (0);
	}
	return (1);
}

int	check_if_too_many(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i >= 3)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	cd(char **cmd, t_env_list **env)
{
	t_env	*env_value;
	char	*value;

	if (check_if_too_many(cmd) == 1)
		return (1);
	if (cmd[1] == NULL || !ft_strcmp(cmd[1], "~"))
	{
		env_value = find_env_by_key(*env, "HOME");
		if (!env_value)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		value = env_value->value;
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		env_value = find_env_by_key(*env, "OLDPWD");
		if (!cd1(env_value))
			return (0);
		value = env_value->value;
	}
	else
		value = cmd[1];
	return (ft_cd(cmd, value, env));
}

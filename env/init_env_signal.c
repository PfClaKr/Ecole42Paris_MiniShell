/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:46:44 by ychun             #+#    #+#             */
/*   Updated: 2023/02/20 18:18:30 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_global.child == 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
			g_global.ret = 130;
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 1);
		}
	}
}

int	init_env(char *origin, char **key, char **value)
{
	int		i;

	i = -1;
	while (origin[++i])
	{
		if (origin[i] == '=')
			break ;
	}
	*key = ft_substr(origin, 0, i);
	*value = ft_substr(origin, i + 1, ft_strlen(origin) - i);
	if (!*key || !*value)
		return (-1);
	return (0);
}

void	set_signal(void)
{
	struct termios	term;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &term);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	init_env_signal(char **env, t_env_list **env_list)
{
	t_env		*new_env;
	t_env_list	*tmp_env_list;
	t_env_list	*new_env_list;

	new_env_list = NULL;
	set_signal();
	if (!env || !*env)
		ft_error("Environement NULL\n", STDERR_FILENO);
	while (*env)
	{
		new_env = ft_new_env();
		tmp_env_list = ft_lstnew(new_env);
		if (!new_env || !tmp_env_list)
			ft_error("Allocation memory failed", STDERR_FILENO);
		new_env->origin = ft_strdup(*env);
		if (new_env->origin == NULL)
			ft_error("Allocation memory failed", STDERR_FILENO);
		if (init_env(new_env->origin, &(new_env->key),
				&(new_env->value)) == ERROR)
			ft_error("Allocation memory failed", STDERR_FILENO);
		ft_lstadd_back(&new_env_list, tmp_env_list);
		env++;
	}
	*(env_list) = new_env_list;
}

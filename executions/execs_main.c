/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:11:32 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 12:13:39 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line != NULL)
	{
		i++;
		cmd_line = cmd_line->next;
	}
	return (i * 2);
}

int	count_env_vars(t_env_list *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*get_path(t_env_list *env)
{
	while (env != NULL)
	{
		if (ft_strncmp("PATH", env->content->key, 5) == 0)
			return (env->content->value);
		env = env->next;
	}
	return (NULL);
}

int	exec(t_cmd_line *cmd_line, t_env_list **env)
{
	t_exec		exec;
	t_cmd_line	*tmp;

	exec.pipe = (int *)malloc(sizeof(int) * count_pipes(cmd_line));
	exec.pipe_nb = count_pipes(cmd_line) / 2;
	if (!exec.pipe)
		ft_error("Allocation error", STDERR_FILENO);
	exec.cmd_paths = ft_split(get_path(*env), ':');
	if (create_pipes(&exec, cmd_line) == 0)
		return (0);
	exec.id = -1;
	exec.envp = create_envp_char(*env);
	tmp = cmd_line;
	while (exec.id++ < exec.pipe_nb - 1)
	{
		tmp->begin = cmd_line;
		child(exec, tmp, env);
		if (tmp->next)
			tmp = tmp->next;
	}
	g_global.child = exec.id;
	close_pipes(&exec, cmd_line);
	waiter(&exec, tmp);
	unlink_heredoc_file(cmd_line);
	return (parent_free(&exec, cmd_line), ft_free_cmd_line(cmd_line), 1);
}

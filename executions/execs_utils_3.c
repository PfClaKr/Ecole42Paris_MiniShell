/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:31:59 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/22 18:09:17 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_exit_free_all(char *argv,
							t_cmd_line *cmd_line,
							t_env_list **env)
{
	ft_free_all_env(env);
	ft_free_cmd_line(cmd_line->begin);
	if (write(0, "\n", 0) != -1)
	{
		ft_putstr_fd("here-document delimited by end-of-file (wanted '", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("')\n", 2);
		free(argv);
		exit(1);
	}
	free(argv);
	exit(2);
}

void	exec_exit_free_all(int ret, t_exec *exec, t_cmd_line *line,
		t_env_list **env)
{
	parent_free(exec, line);
	ft_free_cmd_line(line);
	ft_free_all_env(env);
	exit(ret);
}

void	set_ret(int status)
{
	if (WIFEXITED(status))
		g_global.ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_global.ret = WTERMSIG(status);
		if (g_global.ret != 131)
			g_global.ret = g_global.ret + 128;
	}
}

char	*check_when_no_paths(t_exec *exec, t_cmd_line *line, t_env_list **env)
{
	if (access(line->cmd_args[0], 0) != 0)
	{
		perror(line->cmd_args[0]);
		exec_exit_free_all(127, exec, line->begin, env);
	}
	isdir(exec, line, env);
	return (line->cmd_args[0]);
}

void	waiter(t_exec *exec, t_cmd_line *tmp)
{
	int	status;

	while (exec->id-- >= 0)
	{
		if (tmp->tmp != -1 && waitpid(-1, &status, 0) == tmp->tmp)
			set_ret(status);
	}
	g_global.child = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:05:41 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/20 12:45:36 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_2(t_exec *exec, t_cmd_line *line, t_env_list **env)
{
	if (line->cmd_args[0][0] == '.' && line->cmd_args[0][1] != '.'
		&& line->cmd_args[0][1] != '/')
		return (0);
	if (line->cmd_args[0][0] == '.' || line->cmd_args[0][0] == '/')
	{
		if (access(line->cmd_args[0], 0) != 0)
		{
			perror(line->cmd_args[0]);
			exec_exit_free_all(127, exec, line->begin, env);
		}
		else
			isdir(exec, line, env);
		return (1);
	}
	return (0);
}

void	check_exceptions(t_exec *exec, t_cmd_line *line, t_env_list **env)
{
	if (ft_strlen(line->cmd_args[0]) == 1 && line->cmd_args[0][0] == '.')
	{
		ft_putstr_fd(".: filename argument required\n", 2);
		exec_exit_free_all(2, exec, line->begin, env);
	}
}

int	check_is_absolute_path(t_exec *exec, t_cmd_line *line, t_env_list **env)
{
	check_exceptions(exec, line, env);
	if (exec->flag == 1)
		if (check_2(exec, line, env) == 1)
			return (1);
	if (exec->flag == -1 && (line->cmd_args[0][0] == '.'
		|| line->cmd_args[0][0] == '/'))
	{
		if (access(line->cmd_args[0], 0) != 0)
		{
			perror(line->cmd_args[0]);
			exec_exit_free_all(127, exec, line->begin, env);
		}
		else
			isdir(exec, line, env);
		return (1);
	}
	return (0);
}

int	get_flag(t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (i < cmd_line->token_count)
	{
		if (cmd_line->token[i].type == ARG)
			return (cmd_line->token[i].flag_quotes);
		i++;
	}
	return (0);
}

void	put_right_message(t_exec *exec, t_cmd_line *cmd_line, t_env_list **env)
{
	char	*str;

	if (!cmd_line->cmd_args[0])
		exec_exit_free_all(0, exec, cmd_line->begin, env);
	if (cmd_line->cmd_args[0] && cmd_line->cmd_args[0][0] == '\0')
		ft_putstr_fd("'': command not found\n", 2);
	else
	{
		str = ft_strjoin(cmd_line->cmd_args[0], ": command not found\n");
		ft_putstr_fd(str, 2);
		free(str);
	}
	exec_exit_free_all(127, exec, cmd_line->begin, env);
}

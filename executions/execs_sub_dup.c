/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_sub_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:21:09 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 12:49:31 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sub_dup(t_exec *exec, t_cmd_line *cmd_line)
{
	if (exec->id == 0)
	{
		if (cmd_line->infile >= 0)
			dup2(cmd_line->infile, 0);
		if (cmd_line->outfile >= 0)
			dup2(cmd_line->outfile, 1);
		else if (exec->pipe_nb > 1)
			dup2(exec->pipe[1], 1);
	}
	else if (exec->id == exec->pipe_nb - 1)
		last_cmd_dup(exec, cmd_line);
	else
	{
		if (cmd_line->infile >= 0)
			dup2(cmd_line->infile, 0);
		else
			dup2(exec->pipe[2 * exec->id - 2], 0);
		if (cmd_line->outfile >= 0)
			dup2(cmd_line->outfile, 1);
		else
			dup2(exec->pipe[2 * exec->id + 1], 1);
	}
}

void	last_cmd_dup(t_exec *exec, t_cmd_line *cmd_line)
{
	if (cmd_line->infile >= 0)
		dup2(cmd_line->infile, 0);
	else
		dup2(exec->pipe[2 * exec->id - 2], 0);
	if (cmd_line->outfile >= 0)
		dup2(cmd_line->outfile, 1);
}

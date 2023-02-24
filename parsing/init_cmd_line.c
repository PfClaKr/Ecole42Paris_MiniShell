/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:19:38 by ychun             #+#    #+#             */
/*   Updated: 2023/02/22 04:42:00 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_line	*new_cmd_line(void)
{
	t_cmd_line	*new_cmds;

	new_cmds = (t_cmd_line *)malloc(sizeof(t_cmd_line));
	if (!new_cmds)
		ft_error("Allocation error", STDERR_FILENO);
	new_cmds->begin = NULL;
	new_cmds->token = NULL;
	new_cmds->next = NULL;
	new_cmds->infile = -1;
	new_cmds->outfile = -1;
	new_cmds->cmd_args = NULL;
	new_cmds->fd = -1;
	return (new_cmds);
}

int	count_token_before_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == T_PIPE)
			break ;
		i++;
		token = token->next;
	}
	return (i);
}

t_cmd_line	*init_cmd_line(t_cmd_line *cmd_line_origin,
	t_token_list *tokens)
{
	int			count_token;
	t_cmd_line	*cmd_line;
	t_token		*new_token;

	new_token = tokens->head;
	while (new_token)
	{
		if (new_token->type == T_PIPE)
			new_token = new_token->next;
		if (!new_token)
			break ;
		cmd_line = new_cmd_line();
		count_token = count_token_before_pipe(new_token);
		cmd_line->token_count = count_token;
		cmd_line->token = (t_token *)malloc(sizeof(t_token)
				* (count_token + 2));
		copy_cmd_line(cmd_line, &new_token);
		ft_cmd_add_back(&cmd_line_origin, cmd_line);
	}
	return (cmd_line_origin);
}

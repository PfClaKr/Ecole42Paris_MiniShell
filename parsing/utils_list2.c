/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:46:23 by ychun             #+#    #+#             */
/*   Updated: 2023/02/23 17:36:56 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnot_sep(t_token **curr)
{
	if (!(*curr)->next)
		return (0);
	if ((*curr)->type == T_WORD || (*curr)->type == T_WORD_NULL)
	{
		if ((*curr)->flag_quotes == 1 && ((*curr)->next->type == T_WORD
				|| (*curr)->next->type == T_WORD_NULL))
			return (1);
		if ((*curr)->next->type == T_WORD || (*curr)->next->type == T_WORD_NULL)
		{
			(*curr) = (*curr)->next;
			return (0);
		}
	}
	if ((*curr)->next->type == T_SINGLE_QUOTES
		|| (*curr)->next->type == T_DOUBLE_QUOTES
		|| (*curr)->next->type == T_WORD
		|| (*curr)->next->type == T_WORD_NULL)
		return (1);
	return (0);
}

void	ft_merge_word_origin(t_token *curr, int status)
{
	char	*tmp1;
	char	*tmp2;

	if (curr->origin && !curr->next->origin)
	{
		tmp1 = curr->origin;
		tmp2 = curr->next->word;
	}
	else if (!curr->origin && curr->next->origin)
	{
		tmp1 = curr->word;
		tmp2 = curr->next->origin;
		status = 1;
	}
	else if (curr->origin && curr->next->origin)
	{
		tmp1 = curr->origin;
		tmp2 = curr->next->origin;
	}
	else
		return ;
	curr->origin = ft_strjoin(tmp1, tmp2);
	if (status != 1)
		free(tmp1);
}

void	copy_cmd_line(t_cmd_line *t_cmd, t_token **head)
{
	int	i;

	i = 0;
	while ((*head)->type != T_PIPE && (*head))
	{
		t_cmd->token[i].word = ft_strdup((*head)->word);
		t_cmd->token[i].type = (*head)->type;
		if ((*head)->origin)
			t_cmd->token[i].origin = ft_strdup((*head)->origin);
		else
			t_cmd->token[i].origin = (*head)->origin;
		t_cmd->token[i].flag_quotes = (*head)->flag_quotes;
		t_cmd->token[i].tail = (*head)->tail;
		t_cmd->token[i].flag_env = (*head)->flag_env;
		t_cmd->token[i].flag_null = (*head)->flag_null;
		i++;
		*head = (*head)->next;
		if (!(*head))
			break ;
	}
	t_cmd->token[i].type = T_NULL;
}

void	ft_cmd_add_back(t_cmd_line **head, t_cmd_line *cmd)
{
	t_cmd_line	*tmp;

	if (!(*head))
	{
		*head = cmd;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

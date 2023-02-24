/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:42:18 by ychun             #+#    #+#             */
/*   Updated: 2023/02/23 17:36:57 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_heredoc_token(t_token **tmp)
{
	if ((*tmp)->type == 32 && (*tmp))
	{
		if ((*tmp)->next && (*tmp)->next->type == T_SPACE)
			(*tmp) = (*tmp)->next->next;
		while ((*tmp) && ((*tmp)->type != T_SPACE && (*tmp)->type != T_PIPE
				&& !((*tmp)->type >= 30 && (*tmp)->type <= 33)))
			(*tmp) = (*tmp)->next;
	}
}

void	ft_token_merge(t_token **curr)
{
	char	*tmp1;
	char	*tmp2;
	int		status;

	while (ft_isnot_sep(curr))
	{
		status = 0;
		tmp1 = (*curr)->word;
		tmp2 = (*curr)->next->word;
		(*curr)->word = ft_strjoin(tmp1, tmp2);
		if (!(*curr)->word)
			ft_error("Allocation Error", STDERR_FILENO);
		free(tmp1);
		ft_merge_word_origin(*curr, status);
		ft_token_remove_next(*curr);
		(*curr)->type = T_WORD;
		(*curr)->flag_quotes = 1;
	}
}

void	remove_space_token(t_token *head)
{
	t_token	*curr;

	curr = head;
	if (!head->next)
		return ;
	while (curr)
	{
		if (!curr->next)
			return ;
		if (curr->next->type == T_SPACE)
		{
			ft_token_remove_next(curr);
			curr = curr->next;
		}
		else if ((curr->type == T_WORD || curr->type == T_SINGLE_QUOTES
				|| curr->type == T_DOUBLE_QUOTES || curr->type == T_WORD_NULL)
			&& (curr->next->type == T_SINGLE_QUOTES
				|| curr->next->type == T_WORD || curr->next->type == T_WORD_NULL
				|| curr->next->type == T_DOUBLE_QUOTES))
			ft_token_merge(&curr);
		else
			curr = curr->next;
	}
}

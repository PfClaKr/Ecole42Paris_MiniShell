/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 05:33:51 by ychun             #+#    #+#             */
/*   Updated: 2023/02/20 19:12:38 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_token_list2(t_token_list *tokens)
{
	t_token	*token_next;
	t_token	*token_head;

	if (!tokens)
		return ;
	token_head = tokens->head;
	token_next = token_head->next;
	while (token_next)
	{
		if (token_head->word)
			free(token_head->word);
		if (token_head->origin)
			free(token_head->origin);
		free(token_head);
		token_head = token_next;
		token_next = token_next->next;
	}
	if (token_head->word)
		free(token_head->word);
	if (token_head->origin)
		free(token_head->origin);
	free(token_head);
	free(tokens);
}

void	ft_free_cmd_line(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp_line;
	t_cmd_line	*prev_line;

	tmp_line = cmd_line;
	while (tmp_line)
	{
		i = -1;
		while (tmp_line->token[++i].type != T_NULL)
		{
			if (tmp_line->token[i].word)
				free(tmp_line->token[i].word);
			if (tmp_line->token[i].origin)
				free(tmp_line->token[i].origin);
		}
		free(tmp_line->token);
		prev_line = tmp_line;
		tmp_line = tmp_line->next;
		free(prev_line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:34:30 by ychun             #+#    #+#             */
/*   Updated: 2023/02/23 13:59:25 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_syntax_error(t_token *err, t_token *next, t_token *prev, int status)
{
	if ((err->type == T_PIPE && status != 1)
		&& ((!next || next->type != T_PIPE) || prev->word == NULL))
		return (ERR_SYNTAX_PIPE);
	if (!next && status != 1)
		return (ERR_SYNTAX_NEWLINE);
	if (status == 1)
	{
		next->type = ERR_AMBIGUOUS;
		return (ERR_AMBIGUOUS);
	}
	next->type = ERR_SYNTAX;
	return (ERR_SYNTAX);
}

void	con_error_status(t_token_list *token_list, int status,
		int heredoc)
{
	if (status == ERR_SYNTAX_PIPE)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (status == ERR_SYNTAX_NEWLINE)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (status == ERR_SYNTAX)
		con_error_status3(token_list, status);
	if (status == -5)
	{
		ft_free_token_list2(token_list);
		return ;
	}
	if (heredoc == 1)
		syntax_error_heredoc(token_list);
	ft_free_token_list2(token_list);
}

void	con_error_status2(int status)
{
	if (status == -1)
	{
		ft_putstr_fd("unexpected EOF while looking for matching `\''\n", 2);
		ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	}
	if (status == -2)
	{
		ft_putstr_fd("unexpected EOF while looking for matching `\"'\n", 2);
		ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	}
	g_global.ret = 2;
}

void	con_error_status3(t_token_list *tokens, int status)
{
	t_token	*tmp;

	tmp = tokens->head;
	while (tmp->type != status)
		tmp = tmp->next;
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(tmp->word, 2);
	ft_putchar_fd('\n', 2);
	g_global.ret = 2;
}

int	syntax_check(t_token *head)
{
	t_token	*curr;
	t_token	*prev;

	curr = head;
	prev = NULL;
	while (curr)
	{
		if (curr->type == T_PIPE
			&& (prev == NULL || curr->next == NULL
				|| ((prev->type != T_WORD && prev->type != T_WORD_NULL)
					&& prev->type != 40 && prev->type != 41
					&& prev->type != 42 && prev->type != 43)
				|| curr->next->type == T_PIPE))
			return (handle_syntax_error(curr, curr->next, prev, 0));
		if (curr->type >= 30 && curr->type <= 33
			&& (curr->next == NULL
				|| (curr->next->type >= 30 && curr->next->type <= 33)
				|| curr->next->type == T_PIPE))
			return (handle_syntax_error(curr, curr->next, prev, 0));
		prev = curr;
		curr = curr->next;
	}
	return (SUCCESS);
}

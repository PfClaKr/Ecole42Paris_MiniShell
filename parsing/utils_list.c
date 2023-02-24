/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:42:00 by ychun             #+#    #+#             */
/*   Updated: 2023/02/23 14:33:50 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_new_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		ft_error("Allocation Error", STDERR_FILENO);
	new_token->word = NULL;
	new_token->type = -1;
	new_token->origin = NULL;
	new_token->flag_quotes = -1;
	new_token->tail = -1;
	new_token->flag_env = -1;
	new_token->next = NULL;
	new_token->flag_null = -1;
	return (new_token);
}

void	ft_token_add_back(t_token **head, t_token *token2)
{
	t_token	*tmp;

	if (!(*head))
	{
		*head = token2;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token2;
}

void	ft_token_free(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->word)
		free(tmp->word);
	if (tmp->origin)
		free(tmp->origin);
	free(tmp);
}

void	ft_token_remove_next(t_token *token)
{
	t_token	*token2;
	t_token	*token3;

	if (!token->next)
		return ;
	token2 = token->next;
	if (!token2->next)
	{
		ft_token_free(token2);
		token->next = NULL;
		return ;
	}
	token3 = token2->next;
	token->next = token3;
	ft_token_free(token2);
}

void	ft_token_add_middle(t_token *start_token)
{
	t_token	*next_token;
	t_token	*new_token;

	new_token = ft_new_token();
	if (!start_token->next)
	{
		ft_token_add_back(&start_token, new_token);
		return ;
	}
	next_token = start_token->next;
	start_token->next = new_token;
	new_token->next = next_token;
}

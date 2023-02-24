/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:47:44 by ychun             #+#    #+#             */
/*   Updated: 2023/02/18 16:48:04 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_tokenizer_pipe(char *cmd, t_token *token, int *idx)
{
	token->word = ft_substr(cmd, *idx, 1);
	token->type = T_PIPE;
}

void	cmd_tokenizer(char *cmd, t_token_list *token_list)
{
	int		idx;
	t_token	*new_token;

	idx = 0;
	while (cmd[idx] == ' ' && cmd[idx])
		idx++;
	while (cmd[idx])
	{
		new_token = ft_new_token();
		if (cmd[idx] == '<' || cmd[idx] == '>')
			cmd_tokenizer_redirection(cmd, new_token, &idx);
		else if (cmd[idx] == '|')
			cmd_tokenizer_pipe(cmd, new_token, &idx);
		else if (cmd[idx] == '\'')
			cmd_tokenizer_single_quotes(cmd, new_token, &idx);
		else if (cmd[idx] == '\"')
			cmd_tokenizer_double_quotes(cmd, new_token, &idx);
		else if (cmd[idx] == ' ')
			cmd_tokenizer_space(cmd, new_token, &idx);
		else
			cmd_tokenizer_word(cmd, new_token, &idx);
		idx++;
		ft_token_add_back(&token_list->head, new_token);
	}
}

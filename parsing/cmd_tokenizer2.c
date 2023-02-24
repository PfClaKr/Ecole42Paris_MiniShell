/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:39:06 by ychun             #+#    #+#             */
/*   Updated: 2023/02/18 16:48:13 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_tokenizer_word(char *cmd, t_token *token, int *idx)
{
	int	start_point;

	start_point = *idx;
	while (cmd[*idx] && cmd[*idx] != ' '
		&& cmd[*idx] != '\'' && cmd[*idx] != '\"'
		&& cmd[*idx] != '<' && cmd[*idx] != '>' && cmd[*idx] != '|')
		(*idx)++;
	token->word = ft_substr(cmd, start_point, *idx - start_point);
	token->type = T_WORD;
	(*idx)--;
}

void	cmd_tokenizer_space(char *cmd, t_token *token, int *idx)
{
	while (cmd[*idx] && cmd[*idx] == ' ')
		(*idx)++;
	token->word = NULL;
	token->type = T_SPACE;
	(*idx)--;
}

void	cmd_tokenizer_single_quotes(char *cmd, t_token *token, int *idx)
{
	int	start_point;

	start_point = *idx;
	(*idx)++;
	while (cmd[*idx] != '\'')
		(*idx)++;
	token->word = ft_substr(cmd, start_point + 1, *idx - start_point - 1);
	token->type = T_SINGLE_QUOTES;
	token->flag_quotes = 1;
}

void	cmd_tokenizer_double_quotes(char *cmd, t_token *token, int *idx)
{
	int	start_point;

	start_point = *idx;
	(*idx)++;
	while (cmd[*idx] != '\"')
		(*idx)++;
	token->word = ft_substr(cmd, start_point + 1, *idx - start_point - 1);
	token->type = T_DOUBLE_QUOTES;
	token->flag_quotes = 1;
}

void	cmd_tokenizer_redirection(char *cmd, t_token *token, int *idx)
{
	if (cmd[*idx + 1] && (cmd[*idx + 1] == '<' && cmd[*idx] == '<'))
	{
		token->word = ft_substr(cmd, *idx, 2);
		token->type = HEREDOC_CHAR;
		(*idx)++;
	}
	else if (cmd[*idx + 1] && (cmd[*idx + 1] == '>' && cmd[*idx] == '>'))
	{
		token->word = ft_substr(cmd, *idx, 2);
		token->type = OUTFILEOVER_CHAR;
		(*idx)++;
	}
	else if (cmd[*idx] == '>')
	{
		token->word = ft_substr(cmd, *idx, 1);
		token->type = OUTFILE_CHAR;
	}
	else if (cmd[*idx] == '<')
	{
		token->word = ft_substr(cmd, *idx, 1);
		token->type = INFILE_CHAR;
	}
}

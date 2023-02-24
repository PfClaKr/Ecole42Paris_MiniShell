/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:37:01 by ychun             #+#    #+#             */
/*   Updated: 2023/02/23 14:40:08 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_space(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == ' ')
			return (1);
	}
	return (0);
}

void	get_new_dollar(t_token *token, int head_dollar,
		t_env_list *env)
{
	int		tail_dollar;
	char	*new_word;

	tail_dollar = find_tail_dollar(token->word,
			head_dollar + 1);
	new_word = get_new_word(token,
			env, head_dollar, tail_dollar);
	if (!token->origin)
		token->origin = ft_strdup(token->word);
	token->flag_env = 1;
	free(token->word);
	if (!ft_strcmp(new_word, ""))
		token->flag_null = 1;
	token->word = new_word;
}

int	check_count_dollar(char *word)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (word[++i])
	{
		if (word[i] == '$')
		{
			i++;
			if (word[i] == '\0')
				return (count);
			if (word[i] == '$' || ft_isalpha(word[i])
				|| word[i] == '_' || word[i] == '?')
				count++;
		}
	}
	return (count);
}

t_token	*re_get_token_list(t_token *token, char *word)
{
	char	**word_split;
	t_token	*tmp_token;
	int		i;

	i = 0;
	word_split = ft_split(word, ' ');
	if (!word_split)
		ft_error("Allocation Error", STDERR_FILENO);
	tmp_token = token;
	free(tmp_token->word);
	tmp_token->word = ft_strdup(word_split[0]);
	tmp_token->type = T_WORD_NULL;
	while (word_split[++i])
	{
		ft_token_add_middle(tmp_token);
		tmp_token = tmp_token->next;
		tmp_token->word = ft_strdup(word_split[i]);
		tmp_token->type = T_WORD_NULL;
		tmp_token->flag_env = 1;
	}
	i = -1;
	while (word_split[++i])
		free(word_split[i]);
	free(word_split);
	return (tmp_token);
}

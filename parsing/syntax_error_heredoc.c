/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 05:46:25 by ychun             #+#    #+#             */
/*   Updated: 2023/02/22 05:54:40 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc2(char *argv)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (buf)
		{
			if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			{
				free(buf);
				break ;
			}
		}
		else
		{
			ft_putstr_fd("here-document delimited by end-of-file\n'", 2);
			break ;
		}
		free(buf);
	}
}

void	syntax_error_heredoc(t_token_list *tokens)
{
	int		j;
	t_token	*token;
	char	*argv;

	j = 0;
	token = tokens->head;
	while (token)
	{
		if (token->type == LIMITOR)
		{
			if (token->flag_env == 1)
			{
				get_random_heredoc(token, j++);
				here_doc2(token->origin);
			}
			else
			{
				argv = ft_strdup(token->word);
				get_random_heredoc(token, j++);
				here_doc2(argv);
				free(argv);
			}
		}
		token = token->next;
	}
}

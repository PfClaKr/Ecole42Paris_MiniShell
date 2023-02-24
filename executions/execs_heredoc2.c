/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:29:55 by ychun             #+#    #+#             */
/*   Updated: 2023/02/22 17:53:13 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unlink_heredoc_file(t_cmd_line *cmd)
{
	int	i;

	while (cmd)
	{
		i = -1;
		while (++i < cmd->token_count)
		{
			if (cmd->token[i].type == LIMITOR)
				unlink(cmd->token[i].word);
		}
		cmd = cmd->next;
	}
}

void	heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		close(0);
	}
}

void	get_random_heredoc(t_token *token, int j)
{
	char	*new_word;
	char	*tmp;

	tmp = ft_itoa(j);
	free(token->word);
	new_word = ft_strjoin(".heredoc_tmp", tmp);
	token->word = new_word;
	free(tmp);
}

void	exec_heredoc2(t_cmd_line *cmd_line, int *i, t_env_list **env, int *j)
{
	char	*argv;
	int		fd;

	if (cmd_line->token[*i].type == LIMITOR)
	{
		if (cmd_line->token[*i].flag_env == 1)
		{
			get_random_heredoc(&cmd_line->token[*i], (*j)++);
			here_doc(cmd_line->token[*i].origin,
				&cmd_line->token[*i],
				cmd_line,
				env);
		}
		else
		{
			argv = ft_strdup(cmd_line->token[*i].word);
			get_random_heredoc(&cmd_line->token[*i], (*j)++);
			here_doc(argv, &cmd_line->token[*i], cmd_line, env);
			free(argv);
		}
		fd = open("/dev/stdin", O_TRUNC | O_CREAT | O_RDWR, 0000644);
		dup2(fd, 0);
	}
}

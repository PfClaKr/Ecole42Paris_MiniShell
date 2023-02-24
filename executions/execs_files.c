/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:43:38 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 13:31:04 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infile(char *word, t_cmd_line *cmd_line, t_exec *exec, t_env_list *env)
{
	if (cmd_line->infile >= 0)
		close(cmd_line->infile);
	cmd_line->infile = open(word, O_RDONLY);
	if (cmd_line->infile == -1)
	{
		perror(word);
		exec_exit_free_all(1, exec, cmd_line->begin, &env);
	}
}

void	outfile(char *word, t_cmd_line *cmd_line, t_exec *exec, t_env_list *env)
{
	if (cmd_line->outfile >= 0)
		close(cmd_line->outfile);
	cmd_line->outfile = open(word, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (cmd_line->outfile >= 0 && ft_strncmp("/dev/stdout", word, 12) == 0)
		cmd_line->outfile = -2;
	if (cmd_line->outfile == -1)
	{
		perror(word);
		exec_exit_free_all(1, exec, cmd_line->begin, &env);
	}
}

void	outfileover(char *word, t_cmd_line *line, t_exec *exec, t_env_list *env)
{
	if (line->outfile >= 0)
		close(line->outfile);
	line->outfile = open(word, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	if (line->outfile >= 0 && ft_strncmp("/dev/stdout", word, 12) == 0)
		line->outfile = -2;
	if (line->outfile == -1)
	{
		perror(word);
		exec_exit_free_all(1, exec, line->begin, &env);
	}
}

// void	heredoc_redirect(t_cmd_line *cmd_line, t_exec *exec, t_env_list *env,
// 	int i)
// {
// 	exec->flag_quotes = cmd_line->token[i].flag_quotes;
// 	if (cmd_line->infile >= 0)
// 		close(cmd_line->infile);
// 	if (cmd_line->token[i].flag_env == 1)
// 		here_doc(cmd_line->token[i].origin, exec, cmd_line, env);
// 	else
// 		here_doc(cmd_line->token[i].word, exec, cmd_line, env);
// }

void	get_files(t_exec *exec, t_cmd_line *cmd_line, t_env_list *env)
{
	int	i;

	i = 0;
	while (i < cmd_line->token_count)
	{
		if (i >= 1 && (cmd_line->token[i - 1].type == 30
				|| cmd_line->token[i - 1].type == 31
				|| cmd_line->token[i - 1].type == 33)
			&& cmd_line->token[i].type == T_WORD_NULL)
		{
			ft_putstr_fd(cmd_line->token[i].origin, 2);
			ft_putstr_fd(": ambigous redirect\n", 2);
			exec_exit_free_all(1, exec, cmd_line->begin, &env);
		}
		if (cmd_line->token[i].type == INFILE
			|| cmd_line->token[i].type == LIMITOR)
			infile(cmd_line->token[i].word, cmd_line, exec, env);
		else if (cmd_line->token[i].type == OUTFILE)
			outfile(cmd_line->token[i].word, cmd_line, exec, env);
		else if (cmd_line->token[i].type == OUTFILEOVER)
			outfileover(cmd_line->token[i].word, cmd_line, exec, env);
		i++;
	}
}

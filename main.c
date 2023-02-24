/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 12:21:36 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_global	g_global;

int	check_heredoc(t_token *token)
{
	while (token->next)
	{
		if (token->type == HEREDOC_CHAR)
		{
			if (token->next->type == LIMITOR)
				return (1);
		}
	token = token->next;
	}
	return (0);
}

int	is_there_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

void	parsing(t_env_list **env_list, char *str)
{
	t_token_list	*token_list;
	t_cmd_line		*cmd_line;
	int				status;
	int				status_heredoc;

	if (is_there_space(str))
		return ;
	cmd_line = NULL;
	token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token_list)
		ft_error("Allocation failed", STDERR_FILENO);
	status = get_token_list(str, *env_list, token_list);
	status_heredoc = check_heredoc(token_list->head);
	if (status < 0)
	{
		con_error_status(token_list, status, status_heredoc);
		return ;
	}
	cmd_line = init_cmd_line(cmd_line, token_list);
	ft_free_token_list2(token_list);
	if (status_heredoc == 1)
		status_heredoc = exec_heredoc(cmd_line, env_list);
	if (status_heredoc == HEREDOC_ERROR)
		return (unlink_heredoc_file(cmd_line), ft_free_cmd_line(cmd_line));
	exec(cmd_line, env_list);
}

void	prompt(t_env_list **env_list)
{
	char	*str;
	int		status;

	while (1)
	{
		str = readline("$> ");
		if (str)
		{
			status = check_quotes_incmd(str);
			if (status < 0)
				con_error_status2(status);
			else
				parsing(env_list, str);
		}
		else
		{
			break ;
		}
		if (ft_strcmp(str, ""))
			add_history(str);
		free(str);
		str = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env_list		*env_list;

	if (ac > 1)
	{
		printf("Too many arguments. Usage: ./minishell\n");
		return (1);
	}
	(void)av;
	g_global.child = 0;
	g_global.ret = 0;
	init_env_signal(envp, &env_list);
	prompt(&env_list);
	rl_clear_history();
	ft_free_all_env(&env_list);
}

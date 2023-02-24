/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:44 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 14:17:31 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(char **cmd, t_env_list *env_list, int flag)
{
	t_env	*tmp_env;

	(void)cmd;
	tmp_env = env_list->content;
	while (env_list)
	{
		if (flag == 1)
		{
			printf("declare -x ");
			printf("%s=\"%s\"\n", tmp_env->key, tmp_env->value);
		}
		else
			printf("%s=%s\n", tmp_env->key, tmp_env->value);
		env_list = env_list->next;
		if (env_list)
			tmp_env = env_list->content;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:26:23 by ychun             #+#    #+#             */
/*   Updated: 2023/02/19 22:42:57 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env_value(t_env_list **env, char *key, char *value)
{
	t_env_list	*tmp_list;
	t_env		*tmp_env;

	tmp_list = *env;
	tmp_env = tmp_list->content;
	while (tmp_list)
	{
		if (!ft_strcmp(tmp_env->key, key))
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(value);
			return ;
		}
		tmp_list = tmp_list->next;
		if (!tmp_list)
			break ;
		tmp_env = tmp_list->content;
	}
	set_new_env(*env, key, value);
}

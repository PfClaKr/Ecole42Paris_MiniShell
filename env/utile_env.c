/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:30:55 by ychun             #+#    #+#             */
/*   Updated: 2023/02/19 20:22:16 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while (*t1)
	{
		if (*t1 != *t2 || !*t1 || !*t2)
			return (*t1 - *t2);
		++t1;
		++t2;
	}
	return (*t1 - *t2);
}

int	ft_lstsize(t_env_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

t_env	*ft_new_env(void)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->key = NULL;
	new_node->value = NULL;
	return (new_node);
}

t_env_list	*ft_lstnew(t_env *new_env)
{
	t_env_list	*new_list;

	new_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_list)
		return (NULL);
	new_list->content = new_env;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_env_list **new_env_list, t_env_list *tmp_env_list)
{
	t_env_list	*last;

	last = *new_env_list;
	if (!(*new_env_list))
		*new_env_list = tmp_env_list;
	else
	{
		while (last->next)
			last = last->next;
		last->next = tmp_env_list;
	}
}

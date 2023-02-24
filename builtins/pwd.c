/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:53 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/17 12:35:32 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(char **cmd)
{
	char	buffer[4096];

	(void)cmd;
	getcwd(buffer, sizeof(buffer));
	if (buffer == NULL)
	{
		perror("pwd");
		return (2);
	}
	printf("%s\n", buffer);
	return (0);
}

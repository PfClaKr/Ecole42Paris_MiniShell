/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:53:01 by ychun             #+#    #+#             */
/*   Updated: 2023/02/19 16:58:20 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_quote_return(int type)
{
	if (type == T_SINGLE_QUOTES)
		return (-1);
	return (-2);
}

int	is_which_quote(char cmd)
{
	if (cmd == '\'')
		return (-1);
	else if (cmd == '\"')
		return (-2);
	else
		return (ERR_SYNTAX_NEWLINE);
}

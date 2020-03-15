/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 09:23:30 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 00:21:34 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
void	error(char *string, int err)
{
	ft_fprintf(1, "dumbash %d: ", err);
	if (err > 0)
	{
		err == E_F_DIR ? ft_fprintf(1, "%s: is a directory\n", string) : 1;
		err ==  E_PERM ? ft_fprintf(1, "%s: Permission denied\n", string) : 1;
		err == E_NO_CMD ? ft_fprintf(1, "%s: command not found\n", string) : 1;
	}
	else
	{
		ft_fprintf(1, "%s\n", strerror(errno));
	}
	exit(err);
}

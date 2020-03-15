/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 06:22:00 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 05:37:12 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_all all, t_cmd *cmd)
{
	int index;
	int	vars;

	index = 1;
	if (cmd->argv[1] && !ft_strcmp(cmd->argv[1], "-n"))
		index++;
	vars = (index == 1);
	while (cmd->argv[index])
		ft_fprintf(cmd->fd, "%s", cmd->argv[index++]);
	if (vars)
		ft_putchar_fd('\n', cmd->fd);
}

void	apply_builtin(t_all	all, t_cmd *cmd, int type)
{
	if (type == ECHO)
		echo(all, cmd);
	else if (type == EXIT)
		exit(0);
}

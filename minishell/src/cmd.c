/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:03:03 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 07:04:37 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return(ECHO);
	else if (!ft_strcmp(cmd, "env"))
		return (ENV);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	else
		return (0);
}

void	execute(t_all all, t_cmd *cmd)
{
	execve(cmd->cmd, cmd->argv, all.list_env);
}

void	apply_cmd(t_all all)
{
	int		type;
	uid_t	parent;
	int		exit;

	while (all.cmd)
	{
		// parent = fork();
		parent = 0;
		if (!parent)
		{
			if (is_path(all.cmd->cmd))
				execute(all, all.cmd);
			if ((type = is_builtin(all.cmd->cmd)) != 0)
				apply_builtin(all, all.cmd, type);
			else
				here_we_go(all, all.cmd);
		}
		else
		{
			// wait(&exit);
			all.exit_value = exit;
		}
		all.cmd = (all.cmd)->next;
	}
}

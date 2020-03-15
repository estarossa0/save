/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_we_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 05:11:23 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 04:39:13 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_path(char *cmd)
{
	int	index;

	index = 0;
	while (cmd[index])
	{
		if (cmd[index++] == '/')
			return (1);
	}
	return (0);
}

void	here_we_go(t_all all, t_cmd *cmd)
{
	char	*path;
	char	**env_tab;

	path = init_path(all, cmd);
	cmd->argv[0] = path;
	env_tab = list_to_tab(all.env);
	execve(path, cmd->argv, env_tab);
	error("", -1);
}

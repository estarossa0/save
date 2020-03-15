/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 09:19:05 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 00:51:06 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_file(char *file, struct stat info, char *cmd)
{
	if ((info.st_mode & S_IFMT) == S_IFDIR)
		error(cmd, E_F_DIR);
}

char	*init_path(t_all all, t_cmd *cmd)
{
	char			**path;
	int				index;
	struct	stat	info;
	char			*full_path;

	index = -1;
	while (all.env)
	{
		if (!ft_strcmp(all.env->var, "PATH"))
		{
			path = ft_split(all.env->value, ':');
			while (path[++index])
			{
				if (path[index][ft_strlen(path[index]) - 1] == '/')
					path[index][ft_strlen(path[index]) - 1] = 0;
				full_path = ft_strjoin(path[index], ft_strjoin("/", cmd->cmd));
				if (stat(full_path, &info) == 0)
				{
					check_file(full_path, info, cmd->cmd);
					return (full_path);
				}
			}
		}
		all.env = all.env->next;
	}
	error(cmd->cmd, E_NO_CMD);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 05:36:38 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 05:40:07 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	cd_home(t_all all, t_cmd *cmd)
{
	char	*home;

	home = NULL;
	while (all.env)
	{
		if ()
	}
}

void			cd(t_all all, t_cmd *cmd)
{
	if (ft_tablen(cmd->argv) < 2)
		cd_home(all, cmd);
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
		cd_oldpwd(all, cmd);
	else
		cd_path(all, cmd);
}

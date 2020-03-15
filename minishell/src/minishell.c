/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 22:55:24 by azorkane          #+#    #+#             */
/*   Updated: 2020/03/07 20:35:18 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_all(t_all all)
{
	t_cmd *save;

	while (all.cmd)
	{
		save = all.cmd->next;
		free_tab(all.cmd->argv, ft_tablen(all.cmd->argv));
		free(all.cmd);
		all.cmd = save;
	}
}

int main(int argc, char **argv, char **list_env)
{
	t_all all;
	int rt ;
	char *line = NULL;


	rt  = 1;
	all.list_env = list_env;
	init_var(&all.env, list_env);
	while (rt == 1)
	{
		all.cmd = NULL;
		ft_fprintf(1, "dumbash$>");
		get_next_line(1, &line);
		init_cmd(&all.cmd, line);
		apply_cmd(all);
		empty_all(all);
	}
}

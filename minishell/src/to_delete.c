/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 06:20:33 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 00:44:04 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	*add_node(t_list **ptr, void *new_node)
{
	t_list *save;

	save = *ptr;
	if (save == NULL)
	{
		*ptr = new_node;
		(*ptr)->next = NULL;
		save = *ptr;
	}
	else
	{
		while (save->next)
			save = save->next;
		save->next = new_node;
		save = save->next;
		save->next = NULL;
	}
	return (save);
}


void	init_var(t_env **env, char **list_env)
{
	int index;
	t_env	*save;

	index = 0;
	while (list_env[index])
	{
		save = (t_env *)add_node((t_list**)env, malloc(sizeof(t_env)));
		save->key = get_var_key(list_env[index]);
		save->value = get_var_value(list_env[index]);
		save->var = list_env[index];
		index++;
	}
}

void	init_cmd(t_cmd **cmd, char *line)
{
	int index;
	t_cmd	*save;
	char	**tab;
	char	**args;
	tab = ft_split(line, ';');
	index = 0;
	while (tab[index])
	{
		save = (t_cmd *)add_node((t_list**)cmd, malloc(sizeof(t_cmd)));
		args = ft_split(tab[index], ' ');
		save->cmd = args[0];
		save->relation = 0;
		save->readtype = 0;
		save->argv = args;
		index++;
	}
}

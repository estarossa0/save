/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 06:24:27 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 00:46:37 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_tab(t_env *env)
{
	char	**tab;
	size_t	len;
	int		index;

	len = ft_lstsize((t_list *) env);
	tab = (char **)malloc(len + 1);
	index = 0;
	while (env)
	{
		tab[index++] = env->var;
		env = env->next;
	}
	tab[index] = NULL;
	return (tab);
}

char	*get_var_key(char *var)
{
	int index;

	index = 0;
	while (var[index] && var[index] != '=')
		index++;
	return (ft_substr(var, 0, index));
}

char	*get_var_value(char *var)
{
	int index;

	index = 0;
	while (var[index] && var[index] != '=')
		index++;
	return (ft_substr(var, index + 1, ft_strlen(var)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 09:26:35 by arraji            #+#    #+#             */
/*   Updated: 2020/03/07 00:09:47 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PATH_H
# define FT_PATH_H
# include "minishell.h"
char	*init_path(t_all all, t_cmd *cmd);
int		is_path(char *);
void	execute(t_all, t_cmd*);
#endif

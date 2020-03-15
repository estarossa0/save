/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 06:11:56 by arraji            #+#    #+#             */
/*   Updated: 2020/03/08 05:38:00 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H
# include "minishell.h"
# define ECHO		1
# define CD			2
# define ENV		3
# define UNSET		4
# define PWD		5
# define EXPORT		6
# define EXIT		7
void	apply_builtin(t_all	all, t_cmd *cmd, int type);
void	cd(t_all all, t_cmd *cmd);
#endif

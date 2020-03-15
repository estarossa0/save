/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 22:55:37 by azorkane          #+#    #+#             */
/*   Updated: 2020/03/08 00:21:18 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "struct.h"
# include "builtin.h"
# include "env.h"
# include "to_delete.h"
# include "path.h"
# include "error.h"
# include "cmd.h"
# define vibe_check write(1, "v", 1);
void	here_we_go(t_all all, t_cmd *cmd);
#endif

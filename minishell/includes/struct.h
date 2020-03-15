#ifndef FT_STRUCT_H
# define FT_STRUCT_H
#include "minishell.h"

typedef struct s_cmd
{
	struct	s_cmd	*next;
	char			*cmd;
	char			**argv;
	int				relation;
	int				readtype;
	char			*output;
	int				fd;
	int				ret_value;
}				t_cmd;

typedef	struct	s_env
{
	struct	s_env	*next;
	char			*key;
	char			*value;
	char			*var;
}				t_env;

typedef	struct	s_all
{
	t_env	*env;
	t_cmd	*cmd;
	int		exit_value;
	char	**list_env;
}				t_all;
#endif

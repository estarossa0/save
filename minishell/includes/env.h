#ifndef FT_ENV_H
# define FT_ENV_H
#include "minishell.h"
char	*get_var_key(char *var);
char	*get_var_value(char *var);
char	**list_to_tab(t_env *env);
#endif

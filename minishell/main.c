#include <libc.h>
#include "minishell.h"
#include "libft.h"





void apply_func(char **args, char **env)
{
	pid_t pid;
	char	**paths;
	int status;
	int	index;
	int	jndex;

	index = -1;
	jndex = -1;
	while (env[++index])
	{
		if (ft_strncmp(get_var_key(env[index]), "PATH", 5) != 0)
			continue;
		paths = ft_split(get_var_value(env[index]), ':');
		while (paths[++jndex])
		{
			pid = fork();
			if (!pid)
			{
				char *str;
				str = ft_strjoin(paths[jndex],ft_strjoin("/", args[0]));
				execve(str, args, env);
			}
			if (pid)
				wait(&status);
		}
	}
}


/*
**	+---------------------------+
**	|	|	|	| $ | \ | ' | " |
**	+---------------------------+
**	|	|	|	| 8 | 4 | 2 | 1 |
**	+---------------------------+
*/

void	check_quotes(t_pars *pars)
{
	if (pars->line[pars->index] == '"')
	{
		if (((pars->vars & BACKSLASH) == BACKSLASH) && (pars->vars = pars->vars ^ BACKSLASH)
		&& (pars->line[pars->index - 1] = -BACKSLASH))
			return ;
		else if (((pars->vars & QUOTE) == QUOTE))
			return ;
		else if (((pars->vars & DQUOTE) == DQUOTE) && (pars->vars = pars->vars ^ DQUOTE)
		&& (pars->line[pars->index] = -1))
			return ;
		else if (((pars->vars & DQUOTE) == 0) && (pars->vars = pars->vars & DQUOTE)
		&& (pars->line[pars->index] = -1))
			return ;
	}
	if (pars->line[pars->index] == '\'')
	{
		if (((pars->vars & QUOTE) == QUOTE) && (pars->vars = pars->vars ^ QUOTE)
		&& (pars->line[pars->index] = -QUOTE))
			return ;
		if (((pars->vars & QUOTE) == 0) && (pars->vars = pars->vars & QUOTE)
		&& (pars->line[pars->index] = -QUOTE))
			return ;
	}
}

void	check_backslash(t_pars *pars)
{
	if (((pars->vars & BACKSLASH) == BACKSLASH))
		pars->vars = pars->vars & 0;
	else if (((pars->vars & BACKSLASH) == 0))
		pars->vars = pars->vars & BACKSLASH;
}

void	check_dollar(t_pars *pars, char car)
{
	if (((pars->vars & DOLLAR) == DOLLAR))
	{
		pars->vars = pars->vars & 0;
		if (car == '"' || car == ' ' || car == 9 || car == '\'')
			return ;
		else
			pars->line[pars->index -1] = -8;
	}
	else if (((pars->vars & DOLLAR) == 0))
		pars->vars = pars->vars & DOLLAR;

}

void	set_delimiter(t_pars *pars)
{
	if (((pars->vars & QUOTE) == QUOTE) || ((pars->vars & DQUOTE) == DQUOTE) || ((pars->vars & BACKSLASH) == BACKSLASH))
		return ;
	else
		pars->line[pars->index] = -69;
}

void	set_indexs(t_pars *pars)
{
	while (pars->line[+pars->index])
	{
		pars->line[pars->index] == '$' || ((pars->vars & DOLLAR) == DOLLAR) ? check_dollar(pars, pars->line[pars->index]) : 1;
		pars->line[pars->index] == '"' || pars->line[pars->index] == '\'' ? check_quotes(pars) : 1;
		pars->line[pars->index] == '\\' || ((pars->vars & BACKSLASH) == BACKSLASH) ? check_backslash(pars) : 1;
		pars->line[pars->index] == ' ' || pars->line[pars->index] == 9 ? set_delimiter(pars) : 1;
		pars->line++;
	}
}

void	pars_line(t_pars *pars)
{
	set_indexs(pars);
}

void	read_line(char **argv, char **env, t_env *list)
{
	t_pars	pars;
	int rt;

	rt = 1;
	while (rt == 1)
	{
		ft_printf("%s", "dumbash$>");
		rt = get_next_line(1, &(pars.line));
		pars_line(&pars);
	}

}

int main(int argc, char **argv, char **env)
{
	char **args;
	t_env *list;

	read_line(argv, env, list);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PIPE 1
#define PV 2
#define write_end 1
#define read_end 1
int	get_size(char **argv, int *type)
{
	int		size = 0;

	*type = 0;
	while(argv[size])
	{
		if (strcmp(argv[size], "|") == 0)
		{
			*type = PIPE;
			return size;
		}
		else if (strcmp(argv[size], ";") == 0)
		{
			if (argv[size + 1])
				*type = PV;
			return size;
		}
		size++;
	}
	return size;
}

void	copy(char **args, char **argv, int size)
{
	int index= 0;
	while(index < size)
	{
		args[index] = argv[index];
		index++;
	}
	args[index] = NULL;
}

void	dup_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

int	execute(char **argv, char **env, int savefd[2])
{
	int	size;
	int	type;
	int	index = 0;
	int		fds[2];
	char	**args;
	pid_t	pid;
	int		status;
	int ret = 0;
	int		exit_value;

	size = get_size(argv, &type);
	args = malloc(sizeof(char*) * (size + 1));
	copy(args, argv, size);
	printf("%d\n", type);
	if (type == PIPE)
	{
		pipe(fds);
		dup_close(fds[write_end], STDOUT_FILENO);
	}
	if (type == PV || type == 0)
		dup2(savefd[1], STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		if (type == PIPE)
			close(fds[read_end]);
		execve(args[0], args, env);
	}
	if (type == PIPE)
	{
		dup_close(fds[read_end], STDIN_FILENO);
		return (execute(&argv[size + 1], env, savefd));
	}
	while ((ret = waitpid(0, &status, 0)) != -1)
	{
		if (ret == pid)
			exit_value = WEXITSTATUS(status);
	}
	if (type == PV)
		return (execute(&argv[size + 1], env, savefd));
	return exit_value;

}


int main(int argc, char **argv, char **env)
{
	int	savefd[2];

	if (argc == 1)
		return 0;
	for (size_t i = 0; i < 2; i++)
	{
		i = 4;
	}
	savefd[0] = dup(0);
	savefd[1] = dup(1);
	execute(&argv[1], env, savefd);
}
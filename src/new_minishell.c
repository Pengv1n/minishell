#include "minishell.h"

char	**build_envp(t_env *env)
{
	char	**envp;
	int	i;

	i = 0;
	envp = malloc(sizeof(char *) * (size_env(env) + 1));
	if (!envp)
		exit(EXIT_FAILURE);
	while (env)
	{
		envp[i++] = env->data;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	child_minishell(t_env *env)
{
	char	**data;
	static char *path[] = {"minishell", NULL};
	t_env	*pwd;
	char	*min;

	data = build_envp(env);
	pwd = find_env_data(env, "PWD=");
	if (!pwd)
		return (1);
	min = ft_strjoin(pwd->data + 4, "/minishell");
	if (execve(min, path, data))
	{
		free(data);
		exit(1);
	}
	return (0);
}

void	made_new_minishell(t_env *env)
{
	int	pid;
	int	sig;

	pid = fork();
	if (pid == 0)
	{
		if (child_minishell(env))
			return ;
	}
	else
		waitpid(pid, &sig, 0);
	g_return_code = WEXITSTATUS(sig);
	if (!g_return_code && WIFSIGNALED(sig))
		g_return_code = 128 + WTERMSIG(sig);
}
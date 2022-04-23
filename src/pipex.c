#include "minishell.h"

void	waitpid_and_return(t_pipe *pipex, int count)
{
	int	sig;

	waitpid(pipex->pids[count], &sig, 0);
	g_return_code = WEXITSTATUS(sig);
	if (!g_return_code && WIFSIGNALED(sig))
		g_return_code = 128 + WTERMSIG(sig);
}

void	multiple_commands(t_env **env, t_cmd *s, t_msh *msh, t_pipe *pipex)
{
	int	count;

	count_pipes(pipex, msh);
	child_process(pipex, s, msh, env);
	close_fd(pipex->fds);
	close_inout(s);
	count = -1;
	signal_for_main_with_fork();
	while (pipex->size-- > 0)
		waitpid_and_return(pipex, ++count);
	count = -1;
	while (pipex->fds[++count])
		free(pipex->fds[count]);
	free(pipex->fds);
}

void	check_fds(t_cmd *s)
{
	if (s->in < 0)
		error(1, NULL);
	else if (s->in > 0)
	{
		if (dup2(s->in, STDIN_FILENO) < 0)
			error(1, NULL);
		close(s->in);
	}
	if (s->out > 1)
	{
		if (dup2(s->out, STDOUT_FILENO) < 0)
			error(1, NULL);
		close(s->out);
	}
}

void	single_command(t_env **env, t_cmd *s, t_msh *msh, t_pipe *pipex)
{
	char	**envp;

	if (check_if_build_in_or_null(env, s, msh, 1))
		return ;
	pipex->pids[0] = fork();
	if (pipex->pids[0] < 0)
		ft_putstr_fd("Can't make a fork\n", 2);
	if (pipex->pids[0] == 0)
	{
		envp = build_envp(*env);
		child_signals();
		if_no_first_command(s);
		pipex->com[0] = add_dir(pipex, s->cmd, envp);
		check_fds(s);
		if (execve(pipex->com[0], pipex->cmd, envp) < 0)
			error(1, pipex->com[0]);
	}
	close_inout(s);
	signal_for_main_with_fork();
	waitpid_and_return(pipex, 0);
}

void	alloc_pipex(t_pipe *pipex, t_msh *msh)
{
	pipex->pids = malloc(sizeof(int) * (msh->amount + 1));
	if (!pipex->pids)
		error(1, NULL);
	pipex->pids[msh->amount] = '\0';
	pipex->com = malloc(sizeof(char *) * (msh->amount + 1));
	if (!pipex->com)
		error(1, NULL);
	pipex->com[msh->amount] = "\0";
}

void	pipex(t_cmd *s, t_msh *msh, t_env *env)
{
	t_pipe	pipex;

	ignore_signals();
	if (s->cmd && s->cmd[0] && (!ft_strncmp(s->cmd[0], "minishell", 10)
		|| !ft_strncmp(s->cmd[0], "./minishell", 12))
		&& msh->amount == 1)
	{
		made_new_minishell(env);
		return ;
	}
	alloc_pipex(&pipex, msh);
	if (msh->amount == 1)
		single_command(&env, s, msh, &pipex);
	else
		multiple_commands(&env, s, msh, &pipex);
	free(pipex.com);
	free(pipex.pids);
}
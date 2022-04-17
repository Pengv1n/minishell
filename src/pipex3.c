#include "minishell.h"

void	first_child(t_cmd *s, t_pipe *pipex)
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
	else if (dup2(pipex->fds[pipex->size][1], STDOUT_FILENO) < 0)
		error(1, NULL);
}

void	middle_child(t_cmd *s, t_pipe *pipex)
{
	if (s->in > 0)
	{
		if (dup2(s->in, STDIN_FILENO) < 0)
			error(1, NULL);
		close(s->in);
	}
	else if (dup2(pipex->fds[pipex->size - 1][0], STDIN_FILENO) < 0)
		error(1, NULL);
	if (s->out > 1)
	{
		if (dup2(s->out, STDOUT_FILENO) < 0)
			error(1, NULL);
		close(s->out);
	}
	else if (dup2(pipex->fds[pipex->size][1], STDOUT_FILENO) < 0)
		error(1, NULL);
}

void	last_child(t_cmd *s, t_pipe *pipex)
{
	if (s->in > 0)
	{
		if (dup2(s->in, STDIN_FILENO) < 0)
			error(1, NULL);
		close(s->in);
	}
	else if (dup2(pipex->fds[pipex->size - 1][0], STDIN_FILENO) < 0)
		error(1, NULL);
	if (s->out > 1)
	{
		if (dup2(s->out, STDOUT_FILENO) < 0)
			error(1, NULL);
		close(s->out);
	}
}

void	do_process(t_cmd *s, t_msh *msh, t_pipe *pipex)
{
	if (pipex->size == 0)
		first_child(s, pipex);
	else if (pipex->size != msh->amount - 1)
		middle_child(s, pipex);
	else
		last_child(s, pipex);
}

void	child(t_pipe *pipex, t_cmd *s, t_msh *msh, t_env **env)
{
	int	num;
	char	**envp;

	num = !check_if_build_in_or_null(env, s, msh, 0);
	if (!num && !s->cmd)
		exit(0);
	envp = build_envp(*env);
	child_signals();
	if_no_first_command(s);
	if (num)
		pipex->com[pipex->size] = add_dir(pipex, s->cmd, envp);
	if (num || (!num && (s->out == 1)))
		do_process(s, msh, pipex);
	close_fd(pipex->fds);
	if (!num)
		choose_build_in_function(env, s, msh, 1);
	else if (execve(pipex->com[pipex->size], pipex->cmd, envp) < 0)
		error(1, pipex->com[pipex->size]);
}

void	child_process(t_pipe *pipex, t_cmd *s, t_msh *msh, t_env **env)
{
	pipex->size = -1;
	while (++pipex->size < msh->amount)
	{
		if (pipex->size > 0)
			s = s->next;
		pipex->pids[pipex->size] = fork();
		if (pipex->pids[pipex->size] < 0)
			error_with_std_function(21);
		if (pipex->pids[pipex->size] == 0)
			child(pipex, s, msh, env);
	}
}

void	count_pipes(t_pipe *pipex, t_msh *msh)
{
	int	count;

	count = -1;
	pipex->fds = malloc(sizeof(int *) * (msh->amount));
	if (!pipex->fds)
		error_with_std_function(10);
	while (++count < msh->amount - 1)
	{
		pipex->fds[count] = malloc(sizeof(int) * 2);
		if (!pipex->fds[count])
			error_with_std_function(11);
		if (pipe(pipex->fds[count]) == -1)
		{
			while (count > -1)
			{
				free(pipex->fds[count]);
				pipex->fds[count--] = NULL;
			}
			free(pipex->fds);
			error_with_std_function(20);
		}
	}
	pipex->fds[count] = NULL;
}
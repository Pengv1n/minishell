#include "minishell.h"

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

	}
}

void	alloc_pipex(t_pipe *pipex, t_msh *msh)
{
	pipex->pids = malloc(sizeof(int) * msh->amount + 1);
	if (!pipex->pids)
		error(1, NULL);
	pipex->pids[msh->amount] = '\0';
	pipex->com = malloc(sizeof(char *) * msh->amount + 1);
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

}
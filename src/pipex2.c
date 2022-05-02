#include "minishell.h"

char	*check_commands(t_pipe *descriptor, char *cmd)
{
	char	*add_dir;
	int	cnt;

	cnt = 0;
	while (descriptor->path[cnt])
	{
		add_dir = ft_strjoin(descriptor->path[cnt++], cmd);
		if (access(add_dir, 0) == 0)
		{
			free_double_massive(descriptor->path);
			free(cmd);
			cmd = NULL;
			return (add_dir);
		}
		free(add_dir);
		add_dir = NULL;
	}
	free_double_massive(descriptor->path);
	free(cmd);
	cmd = NULL;
	error(2, descriptor->cmd[0]);
	return (NULL);
}

char	*add_slash(t_pipe *descriptor)
{
	char	**slash;
	char	*add_slsh;
	int	cnt;

	cnt = 0;
	slash = NULL;
	if (access(descriptor->cmd[0], 0) < 0)
		error(1, descriptor->cmd[0]);
	slash = ft_split(descriptor->cmd[0], '/');
	if (!slash)
	{
		ft_putstr_fd("error with malloc\n", 2);
		exit(EXIT_FAILURE);
	}
	while (slash[cnt])
		cnt++;
	add_slsh = ft_strjoin("/", slash[cnt - 1]);
	if (!add_slsh)
	{
		ft_putstr_fd("error with malloc\n", 2);
		exit(EXIT_FAILURE);
	}
	free(slash);
	slash = NULL;
	return (add_slsh);
}

char	*no_path(t_pipe *descriptor, char **cmd)
{
	if (access(cmd[0], 0) < 0)
		return (cmd[0]);
	descriptor->path = ft_split(cmd[0], ':');
	descriptor->cmd = cmd;
	return (cmd[0]);
}

char	*add_dir(t_pipe *descriptor, char **cmd, char **envp)
{
	const char	str[] = "PATH=";
	char	*dir;
	char	*path;
	char	*add_slsh;
	int	cnt;

	add_slsh = NULL;
	path = NULL;
	dir = NULL;
	cnt = 0;
	while (envp && envp[cnt] && ft_strncmp(str, envp[cnt], ft_strlen(str)))
		cnt++;
	if (!envp[cnt])
		return (no_path(descriptor, cmd));
	path = ft_strchr(envp[cnt], '=') + 1;
	descriptor->path = ft_split(path, ':');
	descriptor->cmd = cmd;
	if (ft_strchr(descriptor->cmd[0], '/'))
		add_slsh = add_slash(descriptor);
	else
		add_slsh = ft_strjoin("/", descriptor->cmd[0]);
	if (!add_slsh)
		error_with_std_function(14);
	dir = check_commands(descriptor, add_slsh);
	if (!dir)
		error_with_std_function(15);
	return (dir);
}

void	close_inout(t_cmd *s)
{
	while (s)
	{
		if (s->in > 0)
			close(s->in);
		if (s->out > 1)
			close(s->out);
		s = s->next;
	}
}

void	if_no_first_command(t_cmd *s)
{
	if (!ft_strlen(s->cmd[0]))
	{
		close_inout(s);
		error(2, s->cmd[0]);
	}
}
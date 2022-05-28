/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:41:39 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:41:41 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int **fds)
{
	int	cnt1;
	int	cnt2;

	cnt1 = -1;
	while (fds[++cnt1])
	{
		cnt2 = 0;
		while (cnt2 < 2 && fds[cnt1][cnt2])
		{
			close(fds[cnt1][cnt2]);
			cnt2++;
		}
	}
}

char	*check_commands(t_pipe *descriptor, char *cmd)
{
	char	*add_dir;
	int		cnt;

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

void	waitpid_and_return(t_pipe *pipex, int count)
{
	int	sig;

	waitpid(pipex->pids[count], &sig, 0);
	g_return_code = WEXITSTATUS(sig);
	if (!g_return_code && WIFSIGNALED(sig))
		g_return_code = 128 + WTERMSIG(sig);
}

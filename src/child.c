/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:41:39 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:41:41 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

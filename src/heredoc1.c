/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:51:25 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:51:27 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_proc_heredoc(t_list *cmd_data, int save, t_cmd *s)
{
	char	*cmd;

	cmd = NULL;
	signal_for_heredoc();
	while (1)
	{
		cmd = readline("> ");
		if (!ft_strncmp(cmd, cmd_data->content,
				ft_strlen(cmd_data->content) + 1))
			break ;
		if (save)
		{
			write(s->in, cmd, ft_strlen(cmd));
			write(s->in, "\n", 1);
		}
		free(cmd);
	}
	free(cmd);
	exit(0);
}

void	start_new_readline(t_list *cmd_data, int save, t_cmd *s)
{
	int	pid;

	if (save)
		open_file_for_heredoc(s);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child_proc_heredoc(cmd_data, save, s);
	else
	{
		ignore_signals();
		wait(NULL);
	}
	if (save)
	{
		close(s->in);
		s->in = open (s->hr_name, O_RDONLY, 0644);
	}
	sig_msh();
}

int	check_if_saved_in(t_list *cmd_data)
{
	while (cmd_data)
	{
		if ((!ft_strncmp(cmd_data->content, "<", 2)
				&& !cmd_data->flag_in_quotes)
			|| (!ft_strncmp(cmd_data->content, "<<", 3)
				&& !cmd_data->flag_in_quotes))
			return (0);
		if (data_is_pipe(cmd_data))
			return (1);
		cmd_data = cmd_data->next;
	}
	return (1);
}

t_list	*check_type_readline(t_list *cmd_data, t_cmd *s)
{
	start_new_readline(cmd_data, check_if_saved_in(cmd_data), s);
	return (cmd_data->next);
}

void	heredoc(t_list *cmd_data, t_cmd *s)
{
	while (cmd_data)
	{
		if (!ft_strncmp(cmd_data->content, "<<", 3)
			&& !cmd_data->flag_in_quotes)
			cmd_data = check_type_readline(cmd_data->next, s);
		else
			cmd_data = cmd_data->next;
		if (cmd_data && data_is_pipe(cmd_data))
			s = s->next;
	}
}

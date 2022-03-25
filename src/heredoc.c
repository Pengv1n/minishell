#include "minishell.h"

int	data_is_pipe(t_list *cmd_data)
{
	if ((!ft_strncmp(cmd_data->content, "|", 2) && !cmd_data->flag_in_quotes))
		return (1);
	return (0);
}

char	*create_hd(const char *str)
{
	int	num;
	char	*number;
	char	*new_str;

	num = 1;
	new_str = NULL;
	number = ft_itoa(num++);
	if (!number)
		exit(EXIT_FAILURE);
	new_str = ft_strjoin(str, number);
	if (!new_str)
		exit(EXIT_FAILURE);
	free(number);
	while (access(new_str, R_OK) == 0)
	{
		free(new_str);
		number = ft_itoa(num++);
		if (!number)
			exit(EXIT_FAILURE);
		new_str = ft_strjoin(str, number);
		if (!new_str)
			exit(EXIT_FAILURE);
		free(number);
	}
	return (new_str);
}

void	open_file_for_heredoc(t_cmd *s)
{
	const char	str[] = ".file";

	if (access(str, F_OK) == 0)
	{
		s->hr_name = create_hd(str);
		s->in = open(s->hr_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (s->in < 0)
			exit(EXIT_FAILURE);
	}
	else
	{
		s->in = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (s->in < 0)
			exit(EXIT_FAILURE);
		s->hr_name = ft_strdup(str);
	}
}

void	child_proc_heredoc(t_list *cmd_data, int save, t_cmd *s)
{
	char	*cmd;

	cmd = NULL;
	signal_for_heredoc();
	while (1)
	{
		cmd = readline("> ");
		if (!ft_strncmp(cmd, cmd_data->content, ft_strlen(cmd_data->content) + 1))
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
		if ((!ft_strncmp(cmd_data->content, "<", 2) && !cmd_data->flag_in_quotes)
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
		if (!ft_strncmp(cmd_data->content, "<<", 3) && !cmd_data->flag_in_quotes)
			cmd_data = check_type_readline(cmd_data->next, s);
		else
			cmd_data = cmd_data->next;
		if (cmd_data && data_is_pipe(cmd_data))
			s = s->next;
	}
}
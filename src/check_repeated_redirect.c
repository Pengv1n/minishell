#include "minishell.h"

int	data_pipe_or_redirect(t_list *cmd_data)
{
	char	*data;

	data = cmd_data->content;
	if (cmd_data->flag_in_quotes)
		return (0);
	if (!ft_strncmp(data, ">", 2) || !ft_strncmp(data, "<", 2)
			|| !ft_strncmp(data, ">>", 3) || !ft_strncmp(data, "<<", 3)
			|| !ft_strncmp(data, "|", 2))
		return (1);
	return (0);
}

int	ft_pipe_error(t_list *cmd_data)
{
	if (!ft_strncmp(cmd_data->content, "|", 2))
		printf("minishell: syntax error near unexpected token `|'\n");
	else
		printf("minishell: syntax error near unexpected token `newline'\n");
	return (1);
}

int	both_data_spec_symbols(char *op, char *next_op)
{
	if ((!ft_strncmp(op, "|", 2) && !ft_strncmp(next_op, "|", 2))
		|| ((!ft_strncmp(op, ">", 2) || !ft_strncmp(op, "<", 2)
		|| !ft_strncmp(op, ">>", 3) || !ft_strncmp(op, "<<", 3))
			&& !ft_strncmp(next_op, "|", 2)))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if ((!ft_strncmp(op, ">", 2) || !ft_strncmp(op, "<", 2)
		|| !ft_strncmp(op, ">>", 3) || !ft_strncmp(op, "<<", 3))
		&& (!ft_strncmp(next_op, ">", 2) || !ft_strncmp(next_op, "<", 2)
		|| !ft_strncmp(next_op, ">>", 3) || !ft_strncmp(next_op, "<<", 3)))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", next_op);
		return (1);
	}
	return (0);
}

int	check_repited_redirect(t_list *cmd_data)
{
	if ((!cmd_data->next && data_pipe_or_redirect(cmd_data))
		|| (!ft_strncmp(cmd_data->content, "|", 2) && !cmd_data->flag_in_quotes))
		return (ft_pipe_error(cmd_data));
	while (cmd_data->next)
	{
		if (!cmd_data->flag_in_quotes || !cmd_data->next->flag_in_quotes)
		{
			if (both_data_spec_symbols(cmd_data->content, cmd_data->next->content))
				return (1);
		}
		cmd_data = cmd_data->next;
	}
	if (data_pipe_or_redirect(cmd_data))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
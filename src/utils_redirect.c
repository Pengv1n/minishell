#include "minishell.h"

int	data_redirect_in(t_list *cmd_data)
{
	if (cmd_data->flag_in_quotes)
		return (0);
	if (!ft_strncmp(cmd_data->content, "<", 2))
		return (1);
	return (0);
}

int	data_redirect_out(t_list *cmd_data)
{
	if (cmd_data->flag_in_quotes)
		return (0);
	if (!ft_strncmp(cmd_data->content, ">", 2)
		|| !ft_strncmp(cmd_data->content, ">>", 3))
		return (1);
	return (0);
}

t_list	*error_ambitious_data(t_list *cmd_data, t_cmd *s)
{
	s->err = 1;
	s->cmd = NULL;
	printf("minishell: %s: ambiguous redirect\n", cmd_data->amb_data);
	g_return_code = 1;
	while (cmd_data && !data_is_pipe(cmd_data))
		cmd_data = cmd_data->next;
	return (cmd_data);
}

t_list	*error_with_redirect(t_list *cmd_data, t_cmd *s)
{
	printf("minishell: %s: %s\n", cmd_data->next->content, strerror(errno));
	s->cmd = NULL;
	s->err = 1;
	while (cmd_data && !data_is_pipe(cmd_data))
		cmd_data = cmd_data->next;
	return (cmd_data);
}

int	check_if_not_last_redirect_in(t_list *cmd_data)
{
	while (cmd_data && !data_is_pipe(cmd_data))
	{
		if (data_redirect_in(cmd_data))
			return (1);
		cmd_data = cmd_data->next;
	}
	return (0);
}

int	check_if_not_last_redirect_out(t_list *cmd_data)
{
	while (cmd_data && !data_is_pipe(cmd_data))
	{
		if (data_redirect_out(cmd_data))
			return (1);
		cmd_data = cmd_data->next;
	}
	return (0);
}
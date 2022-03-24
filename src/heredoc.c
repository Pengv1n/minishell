#include "minishell.h"

int	data_is_pipe(t_list *cmd_data)
{
	if ((!ft_strncmp(cmd_data->content "|", 2) && !cmd_data->flag_in_quotes))
		return (1);
	return (0);
}

t_list	*check_type_readline(t_list *cmd_data, t_cmd *s)
{

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
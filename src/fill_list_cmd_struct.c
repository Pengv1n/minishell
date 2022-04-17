#include "minishell.h"

void	fill_list_cmd_struct(t_list *cmd_data, t_cmd *s)
{
	heredoc(cmd_data, s);
	made_redirect(cmd_data, s);
	add_command_and_args(cmd_data, s);
}
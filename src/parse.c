#include "minishell.h"

void	split_cmd(char *cmd, t_list **cmd_data)
{
	int	i;
	char	*tmp;

	i = -1;
	cmd = ft_strtrim(cmd, " \t\v\b\r");
	tmp = cmd;
	if (!cmd)
	{
		free(cmd);
		return ;
	}
	while (cmd && cmd[++i])
	{
		while (cmd[i] && )
	}
}

void	parse_command(char *command, t_msh *msh, t_env *env)
{
	t_list	*cmd_data;


}
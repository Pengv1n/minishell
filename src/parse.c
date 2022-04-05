#include "minishell.h"

int	check_type(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	check_quote(char *cmd, int i, char quote)
{
	int	j;

	j = i;
	while (cmd[++i])
	{
		if (cmd[i] == quote)
			return (i);
	}
	return (j);
}

char	*split_spec_symbols(t_list **cmd_data, char *cmd, int i)
{
	int	tmp;

	tmp = i;
	if (i > 0)
		ft_lstadd_back(cmd_data, ft_lstnew(ft_substr(cmd, 0, i)));
	while (cmd[i] && (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>'))
		i++;
	ft_lstadd_back(cmd_data, ft_lstnew(ft_substr(cmd, tmp, i - tmp)));
	if (!cmd[i])
		return (NULL);
	return (cmd + i);
}

char	*add_to_list(char *cmd, int i, t_list **cmd_data)
{
	int	tmp;
	char	*new;

	tmp = i;
	if (!cmd[i])
	{
		ft_lstadd_back(cmd_data, ft_lstnew(ft_strdup(cmd)));
		return (NULL);
	}
	if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
	{
		new = split_spec_symbols(cmd_data, cmd, i);
		while (new && *new == ' ')
			new++;
		return (new);
	}
	while (cmd[i] && cmd[i] == ' ')
		i++;
	ft_lstadd_back(cmd_data, ft_lstnew(ft_substr(cmd, 0 ,tmp)));
	return (cmd + i);
}

void	split_cmd(char *cmd, t_list **cmd_data)
{
	int	i;
	char	*tmp;

	i = 0;
	cmd = ft_strtrim(cmd, " \t\v\b\r");
	tmp = cmd;
	if (!*cmd)
	{
		free(cmd);
		return ;
	}
	while (cmd && cmd[i])
	{
		while (cmd[i] && !check_type(cmd[i]))
		{
			if (cmd[i] == '\'')
				i = check_quote(cmd, i, '\'');
			else if (cmd[i] == '\"')
				i = check_quote(cmd, i, '\"');
			i++;
		}
		cmd = add_to_list(cmd, i, cmd_data);
		i = 0;
	}
	free(tmp);
}

void	init_cmd_data(t_list *cmd_data)
{
	int	i;

	i = 0;
	while (cmd_data)
	{
		cmd_data->flag_not_change_dollars = 0;
		cmd_data->flag_ambitious_redirect = 0;
		cmd_data->flag_dollar_expanded = 0;
		cmd_data->flag_in_quotes = 0;
		cmd_data->amb_data = NULL;
		cmd_data->num = i;
		cmd_data = cmd_data->next;
		i++;
	}
}

void	parse_command(char *command, t_msh *msh, t_env *env)
{
	t_list	*cmd_data;
    t_cmd   *s;
	t_list	*tmp;

	cmd_data = NULL;
	s = NULL;
	split_cmd(command, &cmd_data);
	if (!cmd_data)
		return ;
	init_cmd_data(cmd_data);
	check_if_path_not_expand(cmd_data, env);
	clean_commands(cmd_data, env);
    if (check_syntax_error(cmd_data) || check_repited_redirect(cmd_data))
    {
        g_return_code = 258;
        ft_lstclear(&cmd_data, (void *)free);
        return ;
    }
    if (!init_cmd_struct(cmd_data, &s, msh))
        return ;
    fill_list_cmd_struct(cmd_data, s);
	pipex(s, msh, env);

//	tmp = cmd_data;
//	while (tmp)
//	{
//		printf("%s\n", tmp->content);
//		tmp = tmp->next;
//	}

	ft_lstclear(&cmd_data, (void *)free);
	clear_list_cmd_struct(&s);
}
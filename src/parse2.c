/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:02:30 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:02:31 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	copy;

	copy = i;
	while (cmd[++i])
	{
		if (cmd[i] == quote)
			return (i);
	}
	return (copy);
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

char	*add_to_list(char *cmd, int i, t_list **data)
{
	int		i_copy;
	char	*new;

	i_copy = i;
	if (!cmd[i])
	{
		ft_lstadd_back(data, ft_lstnew(ft_strdup(cmd)));
		return (NULL);
	}
	if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
	{
		new = split_spec_symbols(data, cmd, i);
		while (new && *new == ' ')
			new++;
		return (new);
	}
	while (cmd[i] && cmd[i] == ' ')
		i++;
	ft_lstadd_back(data, ft_lstnew(ft_substr(cmd, 0, i_copy)));
	return (cmd + i);
}

void	split_cmd(char *cmd, t_list **cmd_data)
{
	int		i;
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

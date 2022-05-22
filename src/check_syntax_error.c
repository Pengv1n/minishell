/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:58:43 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 17:58:45 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_only_redirect_pipe(t_list *cmd_data)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = cmd_data->content;
	len = ft_strlen(tmp);
	if (cmd_data->flag_in_quotes)
		return (0);
	while (tmp[i] && (tmp[i] == '|' || tmp[i] == '>' || tmp[i] == '<'))
		i++;
	if (len == i)
		return (1);
	return (0);
}

int	print_redirect_error(char c)
{
	if (c == '|')
		printf("minishell: syntax error near unexpected token `||'\n");
	else if (c == '<')
		printf("minishell: syntax error near unexpected token `<'\n");
	else if (c == 'n')
		printf("minishell: syntax error near unexpected token `newline'\n");
	return (1);
}

int	case_error_redirect(t_list *cmd_data)
{
	char	*tmp;
	int		len;

	tmp = cmd_data->content;
	len = ft_strlen(tmp);
	if (len > 2)
	{
		printf("minishell: syntax error - unexpected token\n");
		return (1);
	}
	else if (len == 2)
	{
		if (!ft_strncmp(tmp, "||", 3))
			return (print_redirect_error('|'));
		else if (!ft_strncmp(tmp, "><", 3))
			return (print_redirect_error('<'));
		else if (!ft_strncmp(tmp, "<>", 3))
			return (print_redirect_error('n'));
	}
	return (0);
}

int	check_syntax_error(t_list *cmd_data)
{
	while (cmd_data)
	{
		if (check_only_redirect_pipe(cmd_data))
		{
			if (case_error_redirect(cmd_data))
				return (1);
		}
		cmd_data = cmd_data->next;
	}
	return (0);
}

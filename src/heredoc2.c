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

int	data_is_pipe(t_list *cmd_data)
{
	if ((!ft_strncmp(cmd_data->content, "|", 2) && !cmd_data->flag_in_quotes))
		return (1);
	return (0);
}

char	*create_hd(const char *str)
{
	int		num;
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

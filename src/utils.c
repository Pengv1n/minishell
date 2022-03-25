#include "minishell.h"

void	free_double_massive(char **data)
{
	int	i;

	i = -1;
	while (data[++i])
	{
		free(data[i]);
		data[i] = NULL;
	}
	free(data);
	data = NULL;
}

void	clear_list_cmd_struct(t_cmd **s)
{
	t_cmd	*tmp;

	if (!(*s))
		return ;
	while (*s)
	{
		if ((*s)->hr_name)
		{
			unlink((*s)->hr_name);
			(*s)->hr_name = NULL;
		}
		if ((*s)->cmd)
		{
			free_double_massive((*s)->cmd);
		}
		tmp = (*s)->next;
		free(*s);
		*s = tmp;
	}
	*s = NULL;
}
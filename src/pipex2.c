#include "minishell.h"

void	close_inout(t_cmd *s)
{
	while (s)
	{
		if (s->in > 0)
			close(s->in);
		if (s->out > 1)
			close(s->out);
		s = s->next;
	}
}
#include "minishell.h"

void	close_fd(int **fds)
{
	int	i;
	int	j;

	i = -1;
	while (fds[++i])
	{
		j = -1;
		while (fds[i][++j])
			close(fds[i][j]);
	}
}
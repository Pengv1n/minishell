#include "minishell.h"

void	close_fd(int **fds)
{
	int	cnt1;
	int	cnt2;

	cnt1 = -1;
	while (fds[++cnt1])
	{
		cnt2 = 0;
		while (cnt2 < 2 && fds[cnt1][cnt2])
		{
			close(fds[cnt1][cnt2]);
			cnt2++;
		}
	}
}